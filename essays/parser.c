void stmt(void)
{
	int ltype, rtype, symtab_descriptor;
	
	switch(lookahead)
	{
		case BEGIN: match(BEGIN);stmtlist();match(END);
		break;
		case IF:
		
		match(IF);			//	(lbl_else=lbl_endif=loopcount++
		expr(BOOL);			// 		<<expr>>.as
		match(THEN);		//		jz .L$lbl_endif
		stmt();				// 		<<stmt>>.as
		if(lookahead==ELSE)
		{					//(lbl_endif=loopcount++)
			match(ELSE);	//	jmp .L$lbl_endif
			stmt();			//.L$lbl_else:
		}					//	<<stmt>>.as
							//.L:$lbl_endif:
		case WHILE://whlstmt(); 
		break;
		case repeat://repstmt();
		break;
		case ID: smpexpr();
		break;
		default:
	}						
}

void stmtif(void) //criar mesmas funções para outros comandos
{
	match(IF);
	/**/int lbl_else=lbl_endif=loopcount++;/**/
	expr(BOOL);
	match(THEN);
	/**/printf("\tjz .L%d\n",lbl_endif);/**/
	stmt();
	if(lookahead==ELSE){
		/**/lbl_endif = loopcount++;/**/
		match(ELSE);
		stmt();
	}
}
