InputDataLimits = [min(X(1,:)) max(X(1,:)); min(X(2,:)) max(X(2,:))];
NumOfHiddenNeurons = 500;
NumOfOutputNeurons = 1;
HiddenLayerActivationFunc = 'radbas';
OutputLayerActivationFunc = 'purelin';
TrainMethod = 'trainlm';
LearningFunction = 'learngd';
CostFunction = 'mse';
TrainGoal = 0.0001;
TrainEpochs = 50;

nnet = newff(InputDataLimits, [NumOfHiddenNeurons NumOfOutputNeurons],...
		 {HiddenLayerActivationFunc, OutputLayerActivationFunc},...
		 TrainMethod, LearningFunction, CostFunction);

nnet.trainParam.show = 50;
nnet.trainParam.lr = 0.05;
nnet.trainParam.epochs = 300;
nnet.trainParam.goal = 0.0001;
nnet.trainParam.showWindow = true;

nnet = train(nnet, X, Y1);

X1 = X(1,:);
X2 = X(2,:);


