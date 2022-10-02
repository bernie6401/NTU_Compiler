# AcDc Compiler
## Description
* This is a project from NTU (National Taiwan University) course, Compiler Technology of Programming Language.
* First project is aim to 
	* add multiplier and division operation in this compiler
	* let compiler can recognize multi character identifier(variable) name by alphabet string
	* use constant folding to optimize the statement
## How to use?
* You can browse Assignment1.pdf. You must run in Linux OS environment(more conveniently). When you finish the coding, use `$ make` command directly.
* `$ ./AcDc <input sample address> <output file address>`
	* For instance: `$ ./AcDc ../test/sample1.ac ./output`
## Something need to know first
* It can not recognize the bottom line as identifier name.
* It can not print negative value like $1-2=-1$ expression. Actually speaking, it can calculate correctly but it can not print it out.(I'll check it out later.)
* It can not recognize identifier name with numbers