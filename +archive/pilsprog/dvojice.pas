program dvojice;

var
	a : array[0..80000] of boolean;
	i, j, p, s : longint;
	t : string;
	b : array[0..1000] of longint;
begin
	for i := 0 to 80000 do
		a[i] := true;
	a[1] := false;
	for i := 2 to 40000 do
		if (a[i] = true) then
			begin
				j := 2 * i;
				while (j < 80000) do
				begin
					a[j] := false;
					j := j + i;
				end;
			end;
	
	s := 0;
	i := 3;
	repeat
		readln(t);
		if (t <> '') then
		begin
			val(t, p);
			while (s < p) do
			begin
				if ((a[i] = true) and (a[i - 2] = true)) then
				begin
					s := s + 1;
					b[s] := i - 2;
				end;
				i := i + 1;
			end;
			writeln('(', b[p], ', ', (b[p] + 2), ')');
		end;
	until (t = '')
end.
