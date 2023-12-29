/*---------Begin Scanner-------------*/

printf("%10s \t Line number \t %s\n\n", "Token instance", "Token type");
numToken = 0; // extern var
//Token *tokens = (Token *) malloc(numToken * sizeof(Token)); 
tokens = (Token *) malloc(numToken * sizeof(Token)); // extern var 
do {
        numToken++;
        tokens = (Token *)realloc(tokens, numToken * sizeof(Token));
        tokens[numToken - 1] = scanner(filePtr);

        printToken(tokens[numToken - 1]);

} while (tokens[numToken - 1].tokenType != EOFtk);

/*---------/End Scanner-------------*/
