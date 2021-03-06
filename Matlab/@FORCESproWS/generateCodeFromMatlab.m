function generateCodeFromMatlabResult = generateCodeFromMatlab(obj,userID,matFileByteStreamAsString,database)
%generateCodeFromMatlab(obj,userID,matFileByteStreamAsString,database)
%
%     Input:
%       userID = (string)
%       matFileByteStreamAsString = (string)
%       database = (string)
%
%     Output:
%       generateCodeFromMatlabResult = (string)

% Build up the argument lists.
values = { ...
   userID, ...
   matFileByteStreamAsString, ...
   database, ...
   };
names = { ...
   'userID', ...
   'matFileByteStreamAsString', ...
   'database', ...
   };

types = { ...
   '{http://www.w3.org/2001/XMLSchema}string', ...
   '{http://www.w3.org/2001/XMLSchema}string', ...
   '{http://www.w3.org/2001/XMLSchema}string', ...
   };
 % Create the message, make the call, and convert the response into a variable.
soapMessage = createSoapMessage( ...
    'FORCESPro', ...
    'generateCodeFromMatlab', ...
    values,names,types,'document');
response = callSoapService( ...
    obj.endpoint, ...
    'FORCESPro/generateCodeFromMatlab', ...
    soapMessage);
generateCodeFromMatlabResult = parseSoapResponse(response);
