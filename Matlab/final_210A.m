n = 3;
y = rand(n);
y(n,2) = y(n,1);
x = nan(n);

z = zeros(n);
for i=1:n
    z(i,i+1) = 1;
end

x(2:end,1) = y(1:end-1,1);
x(n,1:n-1) = y(n,2:end);

for j = 2:n
    for i=1:n-1
        if isnan(x(i,j-1)) && isnan(x(i+1,j))
            x(i+1,j) = 0;
            x(i,j-1) = y(i,j);
        elseif isnan(x(i,j-1))
            x(i,j-1) = x(i+1,j) + y(i,j);
        elseif isnan(x(i+1,j))
            x(i+1,j) = x(i,j-1) - y(i,j);
        else
            disp(x(i,j-1) - x(i+1,j) - y(i,j));
        end
    end
end

x(1,n) = 0;
for k=1:n
    x(1,n) = x(1,n) - x(k,:)*y(:,k);
end
x(1,n) = x(1,n) / y(n,1);