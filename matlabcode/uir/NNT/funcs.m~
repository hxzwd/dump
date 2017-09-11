

function funs = funcs(frmt, nums)

	

	function y = func2(x)
		y = sin(x);
	end

	function y = func3(x)
		y = cos(x);
	end

	function y = func4(filename, x, del, prec)
		if nargin < 4
			prec = 8;
			if nargin == 2
				del = ' ';
			end
		end
		dlmwrite(filename, x, 'delimiter', del, 'precision', prec);
	end


	function outv = func5(nnet, data, tdata)
		
		outv = {};
		nout = nnet(data);
		errs = tdata - nout;
		aerrs = abs(errs);
		perrs = aerrs./abs(tdata);
		perrs = perrs * 100.0;
		tmp = errs.^2;
		smse = sum(tmp);
		misc_info = [string('neural network name: ') + string(nnet.name) + string('\n')...
			 string('neural network userdata: ') + join(struct2cell(nnet.userdata))];
		outv = {tdata, nout, errs, aerrs, perrs,...
			smse, max(aerrs), max(perrs), misc_info };
				

	end

	function func6(data, fnames, del, prec)
		
		dirname = inputname(1);
		currdir = pwd;
		
		file_list = ls(pwd);
		file_list = string(file_list);
		substr_pos = strfind(file_list, string(dirname));
		disp(string('Current directory is ') + string(currdir));
		if isempty(substr_pos)
			disp(string('Create dir ') + string(dirname));
			mkdir(dirname);
		else
			disp(string('Dir ') + string(dirname) + string(' is existed'));
		end
		
		cd(dirname);
		disp(string('Now directory is ') + string(pwd));
		
		tdata = data{1};
		data = data(2:length(data));

		deffn = [...
				string('nnout.txt'),...
				string('nnerror.txt'),...
				string('nnabse.txt'),...
				string('nnproce.txt'),...
				string('nnsmse.txt'),...
				string('nnmaxabse.txt'),...
				string('nnmaxproce.txt')...
				string('nnmisc.txt')...
			];
		
		if nargin < 4
			prec = 15;
			if nargin < 3
				del = ' ';
				if nargin < 2
					fnames = deffn;
				end
			end
		end
		
		is = 1:1:(length(data) - 4);

		for i = is
			
			dlmwrite(fnames{i}, transpose(data{i}), 'delimiter', del, 'precision', prec);
			disp(fnames{i} + string(' writing complited'));
		end
		
		is = (length(data) - 3):1:length(data);
		File = fopen(fnames(length(fnames)), string('w'));
		foutparams = {};		

		for i = is
			i = i;
		end
		
		foutparams = data(is(1):is(length(is)));

		mperr = foutparams{3};
		maerr = foutparams{2};
		smserr = foutparams{1};
		nout = data{1};
		errs = data{2};
		aerrs = data{3};
		perrs = data{4};
		misc_info_str = join(foutparams{4});
		
		
		perr_pos = find(abs(perrs - mperr) <= 0.0001);

		fprintf(File, string('Misc information:\n\n') +...
			string('Sum squared error is %f\n') +...
			string('Max absolute error is %f\n') +...
			string('Max procent error is %f%%\n\n') +...
			string('Misc information:\n %s\n\n') +...
			string('Max error at [%d] is %f%%\n') +...
			string('Neural network output at [%d] is \t%f\n') +...
			string('Absolute error at [%d] is \t%f\n') +...
			string('True value at [%d] is \t%f\n\n') +...
			string('Neural network output data size is %d\n') +...
			string('Test output data size is %d\n\n'),...
			foutparams{1}, foutparams{2},...
			foutparams{3}, misc_info_str,...
			perr_pos, mperr,...
			perr_pos, nout(perr_pos),...
			perr_pos, aerrs(perr_pos),...
			perr_pos, tdata(perr_pos),...
			length(nout), length(tdata)...
			);
		
		
		disp(fnames(length(fnames)) + string(' writing complited'));
		
		fclose(File);
		cd(currdir);
		disp(string('Back in the ') + string(currdir) + string(' directory'));
	end

	function y = func7(x)
		disp(string(inputname(1)));
		S = whos();
		S = struct2cell(S);
		S = S(1,:);
		S = cellfun(@(x) string(x), S, 'UniformOutput', false);
		S = cellfun(@(x) x{1}, S, 'UniformOutput', false);
		y = inputname(1);
		x = x;
		y = S;
		if length(x) > 1
			y = inputname(1)
		end
	end

	function y = make_databank(nns, data)
		y = {};
		N = length(nns);
		for i = 1:1:N
			M = length(data{i});
			tmp = {};
			tmp2 = [];
			nnet = nns{i};
			tmp{1} = [string(nnet.name) join(struct2cell(nnet.userdata))];
			for j = 1:1:M			
				tmp2(j) = nnet(data{i}(j));
			end
			tmp{2} = tmp2;
			y{i} = tmp;
		end

	end

	function set_global(variable, newname)
%{		
		eval(sprintf(...
			'global %s;', string(newname)));
		eval(sprintf(...
			'%s = %s;', string(newname), string(inputname(1))));
%}
	end

	function y = read_global_data(pattern)
		if ~(nargin == 1) || pattern == 'default'
			pattern = '(?<first>.*)(\.dat)';
		end
		

		default_path = '/home/hjk/code/sem6/uir/NNT';
		fileList = ls(default_path);
		fileList = string(fileList);
		fileList = strsplit(fileList);
		DataFiles = [];
		global GlobalData;
		GlobalData = {};
		EvalString = string('');
		j = 1;
		for i = 1:1:length(fileList)
			if regexp(fileList(i), '.*\.dat') == 1
				if isempty(strfind(fileList(i), '~'))
					names = regexp(fileList(i), '(?<first>.*)(\.dat)', 'names');
					VarName = string(names.first);
					DataFiles = [DataFiles string(fileList(i))];
					disp(string('Read from ') + string(fileList(i)) +...
						string(' in variable: ') + string(VarName));
					format long;
					tmp = dlmread(fileList(i));
					GlobalData{length(GlobalData) + 1} = tmp;
					EvalString = EvalString + sprintf(...
					'global %s; tmp = size(Data{1}{%d}); %s = reshape(Data{1}{%d}, tmp(2), tmp(1));',...
					 VarName, j, VarName, j);
					j = j + 1;
				end	
			end
		end
		y = { GlobalData, DataFiles, sprintf('%s', EvalString) };
		
	end
	
	function y = make_nnet(idata, odata, mse, spread)
		y = newrb(idata, odata, mse, spread); 
	end

	function [nn, nn1, nn2] = get_nets(mse, spread)
		if nargin < 2
			spread = [1 1 1];
			if nargin < 1
				mse = [0.001 0.001 0.001];
			end
		end
		
		if ~(length(mse) == 3)
			mse = [mse(1) mse(1) mse(1)];
		end
		if ~(length(spread) == 3)
			spread = [spread(1) spread(1) spread(1)];
		end
		
		global X;
		global Y1;
		global Y2;
		global Y;
		global X_2;
		global Y_2;
		global Y1_2;
		global Y2_2;
		
		nn = newrb(X, Y, mse(1), spread(1));
		nn1 = newrb(X, Y1, mse(2), spread(2));
		nn2 = newrb(X, Y2, mse(3), spread(3));
		
	end
	

	function y = nnets_settings(nets)
		nn = nets(1); nn1 = nets(2); nn2 = nets(3);
		nn.name = 'NN (x, y) -> (a, b)'; NN = nn.name;
		nn1.name = 'NN1 (x, y) -> a'; NN1 = nn1.name;
		nn2.name = 'NN2 (x, y) -> b'; NN2 = nn2.name;

		SNN = nn.userdata; SNN.Info =  'Field for information'; SNN.Misc = 'Misc data';
		SNN1 = nn1.userdata; SNN1.Info =  'Field for information'; SNN1.Misc = 'Misc data';
		SNN2 = nn2.userdata; SNN2.Info =  'Field for information'; SNN2.Misc = 'Misc data';

		nn.userdata = SNN; nn1.userdata = SNN1;  nn2.userdata = SNN2;
		Comments = [{string('nn_data'), string('nn1_data'), string('nn2_data')}...
			 {string('nn_data_t'), string('nn1_data_t'), string('nn2_data_t')}]; 
		Networks = [nn, nn1, nn2];
		Nns = Networks;
		Names = [string(NN) string(NN1) string(NN2)];
		Udata = [SNN SNN1 SNN2];
		Data = [{X_2, X_2, X_2}, {X, X, X}];
		TData = [{Y_2, Y1_2, Y2_2}, {Y, Y1, Y2}];
		y = {Networks, Names, Udata, Data, TData};
	
	end
	
	function show_info()
		fprintf(...
		'SQUARED_MSE_GOAL = 0.0003397\nSQUARED_MSE1_GOAL = 0.0004160\n');
		fprintf(...
		'SQUARED_MSE2_GOAL_1 = 0.0002656\nSQUARED_MSE2_GOAL_2 = 0.000264\n');
	end
	
	function y = set_nnet_params(nnet, goal, wind, trfcn)

		if nargin < 4
			trfcn = 'trainc';
			if nargin < 3
				wind = false;
				if nargin < 2
					goal = 0.001;
				end
			end
		end

		nnet.trainFcn = trfcn;
		nnet.trainParam.goal = goal;
		nnet.trainParam.showWindow = wind;
		


		y = nnet;
	end

	func_names = [];
	func_pointers = {};

	func_names = [...
		string('Hello message')...
		string('y = sin(x)')...
		string('y = cos(x)')...
		string('proccess data')...
		string('get neural network data')...
		string('write neural network data')...
		string('inputname test')...
		string('create bank of data')...
		string('set global variable')...
		string('read global data')...
		string('create rbf neural network')...
		string('get nn, nn1, nn2')...
		string('set settings for nn, nn1, nn2')...
		string('show information')...
		string('set neural network params')...
		string('y = cos(x)')...
	];
	
	function func1(x)
		if nargin < 1
			for i = 1:1:length(func_names)
				disp(string(i) + sprintf('\t') + func_names(i));
			end
		else
			disp(string('Hello ') + x);
		end
	end

	func_pointers = {...
		@func1,...
		@func2,...
		@func3,...
		@func4,...
		@func5,...
		@func6,...
		@func7,...
		@make_databank,...
		@set_global,...
		@read_global_data,...
		@make_nnet,...
		@get_nets,...
		@nnets_settings,...
		@show_info,...
		@set_nnet_params,...
		@func3,...
		};

	funs = {};
	funs0 = {};
	funs1 = {};
	func_list = [];
	NumOfFuncs = 0;
	Flag = false;
	
	if nargin == 2 && frmt == 2 && length(nums) == 1
		funs = func_pointers{nums};
	end

	if nargin == 0
		frmt = 1;
	end

	if ~(nargin == 2) 
		nums = [];
	end
	if length(nums) == 1
		nums = [nums nums];
	end
		

	funs1{1} = func_names;
	funs1{2} = func_pointers;

	if length(func_pointers) == length(func_names)
		NumOfFuncs = length(func_pointers);
	end
	
	func_list = 1:1:NumOfFuncs;
	
	if length(nums) == 2 && nargin == 2
		func_list = arrayfun(@(x) (x >= nums(1) && x <= nums(2))*x, func_list);
		funs1{1} = [];
		funs1{2} = {};
		Flag = true;
	end
	
		for i = func_list
			if i == 0
				continue
			end
			funs0{i} = {func_pointers{i}, func_names(i)};
			if Flag
				funs1{1} = [funs1{1} func_names(i)];
				funs1{2}{length(funs1{2}) + 1} =  func_pointers{i};
			end
		end
	
	
	
	

	if frmt == 1
		funs = funs1;
	end

	if frmt == 0
		funs = funs0;
	end
	
	
	if NumOfFuncs == 0
		funs = {};
	end
	
		
end


