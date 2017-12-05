var x, y : longint;
begin
    x := 2;
    y := -2;
    while y < -1 do
      begin
      x := y;
      x := x / y;
      x := x / 2;
      end;
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
