classdef GaussianProcess

    properties
        % add properties
        sparse
        sigma_w
        inv_gram
        inv_gram_y
        z
        y_dim
        y
        L_a
        sigma_f
        
    end
    
    methods
        
        function obj = GaussianProcess(sparse, sigma_w, L_a, signal_variance)
            %GaussianProcess Construct an instance of this class
            obj.sparse = sparse;
            obj.sigma_w = sigma_w;
            obj.L_a = L_a;
            
            obj.sigma_f = signal_variance;
        end
        
        function obj = fitGP(obj, x,u,y)
            % Assume x is n_states by n_timesteps
            % Assume u is n_inputs by n_timesteps
            % Assume y is n_outputs by n_timesteps
            
            obj.y_dim = min(size(y));
            obj.inv_gram_y = cell(obj.y_dim,1);
            obj.inv_gram = cell(obj.y_dim,1);
            obj.y = y;
            
            % TODO: introduce some preprocessing/normalization for performance?
            
            obj.z = [x; u];
            
            % Compute inv(K + I * sigma_w) * y
            % Assumes that there is more data than output dimensions
            for i = 1:min(size(y))
                gram = obj.computeGram(obj.z, obj.z, i);
                size_gram = size(gram,1);
                obj.inv_gram{i} = pinv(gram + obj.sigma_w(i) * eye(size_gram));
                obj.inv_gram_y{i} =obj.inv_gram{i} * y(i, :)';
            end
            
            % not sure that an output is needed here
%             model = obj.inv_gram_y;
                
        end
        
        function mu = muD(obj, x, u)
            % Calculate \mu^d(z) = \mu^d([x,u]')= \mu^d(x,u)
            z_input = [x; u];
            t_steps = size(z_input,2);
            
            if isa(x,'sdpvar')
                mu = sdpvar(obj.y_dim, t_steps);
            else
                mu = zeros(obj.y_dim, t_steps);
            end
            
            for k=1:t_steps
                for i=1:obj.y_dim
                    gram_input = obj.computeGram(z_input(:,k), obj.z, i);
                    mu(i,k) = gram_input * obj.inv_gram_y{i};
                end
            end
        end
        
        function mu = mu_sparse(obj, x, u)
            % TODO: figure out how FITC works with noted inducing points
            % Calculate \mu^d(z) = \mu^d([x,u]')= \mu^d(x,u)
            z_input = [x; u];
            mu = zeros(obj.y_dim, 1);
            
            % TODO: I don't think these dimensions are going to work without
            % pruning.
            for i=1:obj.y_dim
                gram_input = obj.computeGram(z_input, obj.z, i);
                mu(i) = gram_input * obj.inv_gram(i) * obj.y(i,:);
            end
            
        end
        
        function sigma = sigmaD(obj,x, u)
            
            % Calculate \sigma_d
            % TODO: sigma and mu both need K_z\bold{z}, optimize this in
            % future.
            % TODO: this outputs a diagonal matrix as we treat each y to be
            % independent in the Hewing paper. Not sure if this should
            % really output a covariance matrix (SA)
            
            z_input = [x; u];
            sigma = [];
            
            for i=1:obj.y_dim
                gram_input = obj.computeGram(z_input, obj.z, i);
                gram_in_in = obj.computeGram(z_input, z_input, i);
                sigma = [sigma,gram_in_in - gram_input * obj.inv_gram{i} * gram_input'];
            end
            sigma = diag(sigma);
        end
        
        function K = computeGram(obj,z1,z2,a)
            % z: should be in R^(dim(X)+dim(u))x(number of samples)
            % difference between z1 and z2 is that one is the training data
            % and the other is input data for prediction. 
            % outputs a square matrix K (Gram) or column vector for
            % posterior prediction
            
            n_samples_1 = size(z1,2);
            n_samples_2 = size(z2,2);
            
            if isa(z1,'sdpvar')
                K = sdpvar(n_samples_1, n_samples_2);
            else
                K = zeros(n_samples_1, n_samples_2);
            end
            
            % K is symmetric, so only compute upper triangle
            for i=1:n_samples_1
                for j=i:n_samples_2
                    K(i,j) = obj.squaredExpKernel(z1(:,i), z2(:,j), obj.L_a{a}, obj.sigma_f(a));
                end
            end
            
            if n_samples_1 == n_samples_2
                % Make the matrix symmetric
                K = (K+K') - eye(size(K,1)).*diag(K);
            end
            
        end
        
        function k_a = squaredExpKernel(obj, z_i, z_j, L_a, signal_var)
            % Define the squared exponential kernel.
            % z_i: in R^n, n = dim(X) + dim(u)
            % z_j: in R^n, n = dim(X) + dim(u)
            % L_a:  lengthscale
            % signal_var: 
            diff_ij = z_i - z_j;
            k_a = signal_var * exp(-diff_ij'*(L_a\diff_ij));
        end

        function dmudx = gradMuD(obj, x,u)
            % See http://mlg.eng.cam.ac.uk/mchutchon/DifferentiatingGPs.pdf
            % by Andrew McHutchon for derivation
            % TODO: ideally should output a matrix instead of cell array of
            % vectors. Still need to understand the intended dimensions. 
            test_point = [x;u];
            
            out = cell(obj.y_dim,1);
            for i = 1:obj.y_dim
                out{i} = -pinv(obj.L_a{i}) * (test_point - obj.z) * (obj.computeGram(test_point, obj.z, i)' .* obj.inv_gram_y{i});
            end
            
        end
        
    end

    
end