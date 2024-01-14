Program v1;
type
student = record
name:string[10];
group:integer;
ball:array [1..5] of 2..5;
srb:real
end;
var
  st:array[1..10] of student;
  i,j,d:integer;
begin
  for i:=1 to 10 do
  begin
    writeln('Введите фамилию студента');
    readln(st[i].name);
    writeln('Введите номер его группы');
    readln(st[i].group);
    writeln('Введите 5 оценок');
    for j:=1 to 5 do
      readln(st[i].ball[j]);
   d:=0;
   for j:=1 to 5 do d:=d +st[i].ball[j];
   st[i].srb:=d/5;
   end;
 for i:=1 to 10 do
   if st[i].srb>=4 then writeln(st[i].name)
end.

