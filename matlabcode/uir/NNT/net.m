InputFiles = [string('TeachingData_finall.txt') string('TestData_finall.txt')];
DataArrays = {};
format long;


for i = 1:length(InputFiles)
	file = fopen(InputFiles(i), string('r'));
	if file == -1
		continue
	end
	tmp = fscanf(file, ['%f', '%f', '%f', '%f']);
	tmp = reshape(tmp, 4, length(tmp)/4);
	DataArrays{i} = tmp;
end

global X;
global Y1;
global Y2;
global Y;
global X_2;
global Y_2;
global Y1_2;
global Y2_2;

X = DataArrays{1}(1:2,:);
Y = DataArrays{1}(3:4,:);
Y1 = DataArrays{1}(3,:);
Y2 = DataArrays{1}(4,:);

X_2 = DataArrays{2}(1:2,:);
Y_2 = DataArrays{2}(3:4,:);
Y1_2 = DataArrays{2}(3,:);
Y2_2 = DataArrays{2}(4,:);

disp('_________________________________________________________________________________________')
disp('	  |										|')
disp('Переменная|					Данные					|')
disp('__________|_____________________________________________________________________________|')
disp('	  |										|')
disp('    X	  | Обучающие входные данные(пары вида (Центрированное положение СУЗ, Оффсет))	|')
disp('    Y	  | Обучающие выходные данные(пары вида (Центрированное положение СУЗ, Оффсет))	|')
disp('    Y1 	  | Обучающие выходные данные(Центрированное положение СУЗ)			|')
disp('    Y2 	  | Обучающие выходные данные(Оффсет)						|')
disp('__________|_____________________________________________________________________________|')
disp('	  |										|')
disp('    X_2   | Тестовые входные данные(пары вида (Центрированное положение СУЗ, Оффсет))	|')
disp('    Y_2   | Тестовые выходные данные(пары вида (Центрированное положение СУЗ, Оффсет))	|')
disp('    Y1_2  | Тестовые выходные данные(Центрированное положение СУЗ)			|')
disp('    Y2_2  | Тестовые выходные данные(Оффсет)						|')
disp('__________|_____________________________________________________________________________|')


sum_squared_error = 0.001;

InputDataLimits = [min(X(1,:)) max(X(1,:)); min(X(2,:)) max(X(2,:))];
NumOfHiddenNeurons = 200;
NumOfOutputNeurons = 2;
HiddenLayerActivationFunc = 'radbas';
OutputLayerActivationFunc = 'purelin';
TrainMethod = 'trainlm';
LearningFunction = 'learngd';
CostFunction = 'mse';
TrainGoal = 0.00001;
TrainEpochs = 50;

SumSquaredError = 0.01;
Spread = 1;
OutFileName = string('nnout.txt');
PrecVal = 15;


  





