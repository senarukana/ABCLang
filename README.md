# ABC Language
ABC ia a typeless, dynamic language like python and ruby. It's just a toy language right now, just like the name suggest :).
 
Currently, a large part of codes are borrowed from crowbar language which is  written by the . 

## Installation
Simply run make and everything is done.
 
You can set a environment envariable after making it.

    export PATH=$PATH:$ABCLang

### Test your installation
Create a file name hello.abc, put the following:

    println("Hello, world\n");
If you see the "Hello, world" message then your installation is working.


## Control structres
The control structed of ABC are related to C but differ in different way.

####if 
    if a > 0 {
        println("if");
    } else if a < 0 {
        println("else if"");
    } else {
        println("else");
    }
####for
C like for:

    a = {1,2,3};
    for i = 0; i < a.size(); i++ {
       print(a[i]);
    }   
  
easier one:
    #slice
    a = {1, 2, 3};
    for i : a {
        print(i);
    }
    
    n = 10;
    # i will be set to zero automatically
    # default step is one.
    for i : n {
        print(i);
    }
    
    # set step to 2
    for i : n : 2 {
        print(i);
    }

## Functions
Just like python, you don't need to worry about the return value and parameter type.
    
    def calculate(n) {
        # sum will be set to zero the first you use it.
        for i : n {
            sum += i;
        }
        return sum;
    }

multiple return:

    def add_sub(a, b) {
        return a+b, a-b;
    } 
## Data
All the data will be set to zero automatically.
####slice
    s = [1,2,3];
    b = s[:1];
    c = s[:-1];
    
    #two dimention slice
    s2 = new_slice(2,3);
    s2[1] = 5;

####map
    m = {   "hello" : 1,
            "world" : 2,
        };
    m["good"] = 3;
    for name, num : m {
        printf("name=$1, num = $2\n",name, num);
    }
    del m["good"];
## Exception
    try {
        zero = 0;
        a = 3 / zero;
    } catch (e) {
        if e.type == DivisionByZeroException {
            println("opps, div by zero");
         } else {
            throw e;
         }
    }
## IO
Currently it only support fopen, fclose, fgets, fputs operations.
It externs stdin, stdout and stderr as default fd. You can use it just like C.
    
    # read from stdin
    name = fgets(stdin, "what's you name? ")
    printf("your name is $1", name);  

    # write
    try {
        file = fopen("diary", "w+");
        #write
        fputs(file, "what a great day");
    } finnally {
        fclose(file);
    }
    
    # read
    file = fopen(“diary”, "r+");
    for line : file {
        print(line);
    }

## Contact
If you are interested in ABCLang, please feel free to email me: lizhe.ted@gmail.com. If you want to participate in developing this toy lanugage, just fork it and do what you want.

## License MIT


    



    
    
    
  

    

