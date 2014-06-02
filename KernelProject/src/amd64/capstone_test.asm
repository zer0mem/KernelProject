.code

extrn DbgPrint:proc

printf proc
	jmp DbgPrint
printf endp

end
