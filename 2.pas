var many:set of char;
     stroka:string; i:byte;
 begin
   write('Введите строку: ');
   readln(stroka);
   many := [];
   i:=1;
   while i<= length(stroka) do
     if stroka[i] in many
       then delete(stroka,i,1)
       else begin
         many:=many+[stroka[i]];
         inc(i);
       end;
       writeln(stroka);
 end.