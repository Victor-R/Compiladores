var x, y : integer;
begin
    x := 2;
    y := -2;
  repeat
    x := y;
    x := x + 45;
    y := y + 1
  until y < -1;
  if x > 3 then
    begin
      x := 2 * y + 4;
      y :=  7;
    end
  else
    begin
    y := 5;
    x := 4;
    end;
end.
