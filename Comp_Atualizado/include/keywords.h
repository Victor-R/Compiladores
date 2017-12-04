enum {
  BEGIN = 0x4097,
  IF,
  THEN,
  ELSE,
  WHILE,
  DO,
  REPEAT,
  UNTIL,
  VAR,
  BOOLEAN,
  INTEGER,
  REAL,
  DOUBLE,
  /*STRING,
  CHAR,*/
  DIV,
  MOD,
  AND,
  OR,
  NOT,
  TRUE,
  FALSE,
  END
};

extern char *keywords[];
extern int iskeyword(char const *identifier);
