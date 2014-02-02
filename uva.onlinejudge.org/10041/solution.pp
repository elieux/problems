program uva10041;

function readint(): longint;
var
	c: char;
	tmp: longint;
begin
	readint := 0;
	repeat
		read(c);
	until c in ['0'..'9'];
	
	repeat
		val(c, tmp);
		readint := readint * 10 + tmp;
		read(c);
	until not (c in ['0'..'9']);
end;

function total(arr: array of longint; position: longint): longint;
var
	i: longint;
begin
	total := 0;
	for i := low(arr) to high(arr) do begin
		total := total + abs(position - arr[i]);
	end;
end;

function compute_naive(arr: array of longint): longint;
var
	i, min, max, guess, result: longint;
begin
	min := -1;
	max := -1;
	for i := low(arr) to high(arr) do begin
		if (min = -1) or (arr[i] < min) then
			min := arr[i];
		if (max = -1) or (arr[i] > max) then
			max := arr[i];
	end;
	
	compute_naive := -1;
	for guess := min to max do begin
		result := total(arr, guess);
		if (compute_naive = -1) or (result < compute_naive) then
			compute_naive := result;
	end;
end;

function compute_binary(arr: array of longint): longint;
var
	i, min, max, guess, result, guess_plus, guess_minus, result_plus, result_minus, step: longint;
begin
	min := -1;
	max := -1;
	for i := low(arr) to high(arr) do begin
		if (min = -1) or (arr[i] < min) then
			min := arr[i];
		if (max = -1) or (arr[i] > max) then
			max := arr[i];
	end;
	
	compute_binary := -1;
	step := (max - min) div 2;
	guess := min + step;
	result := total(arr, guess);
	repeat
		guess_plus := guess + step;
		guess_minus := guess - step;
		result_plus := total(arr, guess_plus);
		result_minus := total(arr, guess_minus);
		
		if (result_plus >= result) and (result > result_minus) then begin
			guess := guess_minus;
			result := result_minus;
		end else if (result_plus < result) and (result <= result_minus) then begin
			guess := guess_plus;
			result := result_plus;
		end else if (result_plus >= result) and (result <= result_minus) and (step > 1) then begin
			step := step div 2 + step mod 2;
		end else begin
			compute_binary := result;
		end;
	until compute_binary <> -1;
end;

var
	cases: longint;
	relatives: longint;
	i, j: longint;
	arr: array[1..500] of longint;
begin
	cases := readint();
	
	for i := 1 to cases do begin
		relatives := readint();
		for j := 1 to relatives do begin
			arr[j] := readint();
		end;
		
		writeln(compute_binary(arr[1..relatives]));
	end;
end.
