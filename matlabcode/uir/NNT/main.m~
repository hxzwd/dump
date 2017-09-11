function rvalue = main(nns, data, tdata, comment)
	

	default_path = '/home/hjk/code/sem6/uir/NNT';
	rvalue = {};
	
	fileList = ls(default_path);
	fileList = string(fileList);
	fileList = strsplit(fileList);
	DataFiles = [];
	GlobalData = {};

%{	
	for i = 1:1:length(fileList)
		if regexp(fileList(i), '.*\.dat') == 1
			names = regexp(fileList(i), '(?<first>.*)(\.dat)', 'names');
			VarName = string(names.first) + string('_tmp');
			DataFiles = [DataFiles string(fileList(i))];
			disp(string('Read from ') + string(fileList(i)) +...
				string(' in variable: ') + string(VarName));
			eval(sprintf('%s = 0;', VarName));
			eval(sprintf('%s = dlmread(%s);', VarName, fileList(i)));
			eval(sprintf('GlobalData{length(GlobalData)} = %s;', VarName)); 	
		end
	end
%}
	
		

	if nargin == 3
		comment = {string('Empty comment[main.m]')};
	end

	if ~(string('pwd') == string(default_path))
		cd(default_path)
	end

	F = funcs(1, [5 8]);
	make_data = F{2}{1};
	write_data = F{2}{2};
		
	for i = 1:1:length(nns);
		if nargin == 4
			eval(sprintf(...
			'%s = make_data(nns{%d}, data{%d}, tdata{%d});', comment{i}, i, i, i));
			eval(sprintf(...
			'write_data(%s); rvalue{%d} = %s;', comment{i}, i, comment{i}));
		else
			tmp = make_data(nns{i}, data{i}, tdata{i});
			write_data(tmp);
			rvalue{i} = tmp;

		end
	end

end





