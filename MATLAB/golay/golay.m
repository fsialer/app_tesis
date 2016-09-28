function varargout = golay(varargin)
% GOLAY MATLAB code for golay.fig
%      GOLAY, by itself, creates a new GOLAY or raises the existing
%      singleton*.
%
%      H = GOLAY returns the handle to a new GOLAY or the handle to
%      the existing singleton*.
%
%      GOLAY('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in GOLAY.M with the given input arguments.
%
%      GOLAY('Property','Value',...) creates a new GOLAY or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before golay_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to golay_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help golay

% Last Modified by GUIDE v2.5 08-Oct-2015 23:26:14

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @golay_OpeningFcn, ...
                   'gui_OutputFcn',  @golay_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before golay is made visible.
function golay_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to golay (see VARARGIN)

% Choose default command line output for golay
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes golay wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = golay_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;



% --- Executes on button press in pushbutton1.
function pushbutton1_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton1 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
B=dlmread('binario.txt');%lee la matriz del archivo binario.txt
pol = cyclpoly(23, 12, 'min');%Se asigna un polinomio
golay_code = encode(B, 23, 12, 'cyclic', pol);%Codifica una cadena de 12 a 23
cod=fopen('codificado.txt','wt');%Abre el archivo codificado.txt
for i=1:size(golay_code,1)%Bucle para recorrer la fila de la matriz
    for j=1:size(golay_code,2)%Bucle para recorrer la columna d la matriz
        fprintf(cod,'%d',golay_code(i,j));
    end
end
winopen('codificado.txt');%Abre el archivo codificado.txt
fclose(cod);%Cierre el archivo


% --- Executes on button press in pushbutton2.
function pushbutton2_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
dec=dlmread('codigo_extraido.txt');%lee la matriz del archivo codigo_extraido.txt
pol = cyclpoly(23, 12, 'min');%Se asigna un polinomio
message = decode(dec, 23, 12, 'cyclic', pol);%Se decodifica para recuperar los bit del mensaje
d=fopen('decodificado.txt','wt');%Abre el archivo decodificado.txt
for i=1:size(message,1)%Bucle para recorrer la fila de la matriz
    for j=1:size(message,2)%Bucle para recorrer la columna d la matriz
        fprintf(d,'%d',message(i,j));
    end
end
winopen('decodificado.txt');%Abre el archivo decodificado.txt
fclose(d);%Cierre el archivo
