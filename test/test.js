function TEST(NAME,CONDITION) {
  if (!(CONDITION)) { 
    failed_tests += NAME + " ";
    }
  tests++;
  }

var failed_tests = "",tests = 0;
// test null ------------------------------------------------------------------
{ var counter;
  TEST("null 1",null == null);
  TEST("null 2",counter == null);
  TEST("null 3",null == counter);
  TEST("null 4",3 != null);
  TEST("null 5",!(3 == null));
  TEST("null 6",4.0 != null);
  TEST("null 7",!(4.0 == null));
  TEST("null 8","stuff" != null);
  TEST("null 9",!("stuff" == null));
  }

// test strings ---------------------------------------------------------------
{ TEST("string 1","0123456".charAt(3) == "3");
  TEST("string 2","0123456".charCodeAt(3) == 51);
  TEST("string 3","abc".concat("123","456") == "abc123456");
  TEST("string 4","gagagaratzgaratzga".indexOf("ratz") == 6);
  TEST("string 5","gagagaratzgaratzga".lastIndexOf("ratz") == 12);
  TEST("string 6","gagagaratzgaratzga".slice(6,10) == "ratz");
  TEST("string 7","gagagaratzgaratzga".substring(6,10) == "ratz");
  var a = "de en fr ch hallo";
  TEST("string 8",a.split(" ").length == 5);
  TEST("string 9",a.split("").length == a.length);
  TEST("string 10",a.split().length == a.length);
  TEST("string 11",a.split(" ",3).length == 3);
  TEST("string 12",a.split(" ").join(" ") == "de en fr ch hallo");
  }

// test prefix stuff ----------------------------------------------------------
{ var counter = 5;

  TEST("prefix 1",counter == 5);
  TEST("prefix 2",counter++ == 5);
  (++counter)++;
  TEST("prefix 3",counter == 8);
  }

// test variable declaration --------------------------------------------------
{ var broesel = 5,bramm = 1+broesel;
  const brusel = 1;

  TEST("variables 1",broesel == 5);
  TEST("variables 2",bramm == 6);
  TEST("variables 3",brusel == 1);
  
  var u = "HALLO";
  u += "DU!";
  TEST("variables 4",u == "HALLODU!");
  }

// test if --------------------------------------------------------------------
{ if (0) {
    TEST(0,"if 1");
    }
  else {
    }
  
  if (1) {
    }
  else {
    TEST(0,"if 2");
    }
  }


// test while -----------------------------------------------------------------
{ var counter = 0;
  while (counter < 10) counter++;
  TEST("while 1",counter == 10);
  }


// test do-while --------------------------------------------------------------
{ var counter = 0;
  do {
    counter++;
  } while (counter < 10)
  TEST("do-while 1",counter == 10);
  }

// test for -------------------------------------------------------------------
{ var i = 0;

  // this must not cause an error , because for has its own scope
  var counter; 
  
  for (var counter = 0;counter < 10;counter++) {
    i++;
    }
  TEST("for 1",i == 10);
  }

// test for-in ----------------------------------------------------------------
{ const a = new Array(1,1,2,6,24,120,720,5040,40320,362880,3628800);
  var sum = 0;
  
  for (var i in a)
    sum += i;
  TEST("for-in 1",sum == 4037914);
  }

// test scoping ---------------------------------------------------------------
{ var something = 5;
  something;
  
  { something++;
    var something = 7;
    something++;
    }
  TEST("scoping 1",something == 6);
  }

// test functions -------------------------------------------------------------
{ function faculty(n) {
    var counter,result = 1;
    for (counter = 1;counter <= n ;counter++)
      result *= counter;
    return result;
    }
  
  function faculty_recursive(n) {
    if (n <= 1) return 1;
    else return faculty_recursive(n-1)*n;
    }
  
  function product(a,b,c,d) {
    return a*b*c*d;
    }
  
  function spend_some_time() {
    var i = 0;
    while (i < 1000) i++;
    return;
    }

  function assign(x) {
    x = 17;
    }
  
  TEST("functions 1",product(1,2,3,4) == 24);
  TEST("functions 2",faculty(10) == 3628800);
  TEST("functions 3",faculty_recursive(10) == 3628800);
  TEST("functions 4",faculty_recursive(90) == faculty(90));
  spend_some_time();
  
  var u = 4;
  assign(u);
  TEST("functions 5",u == 4);
  }

// test empty statement -------------------------------------------------------
{ function faculty(n) {
    var counter,result = 1;
    for (counter = 1;counter <= n ;counter++)
      result *= counter;
    return result;
    }
  
  var a = new Array(1,1,2,6,24,120,720,5040,40320,362880,3628800),u = 0;
  
  for (var i in a)
    TEST("for-in 1",i == faculty(u++));
  }

// test non-local exits -------------------------------------------------------
{ var i;
  for (i = 0;i < 2000;i++) {
    if (i == 100) break;
    }
  TEST("exits 1",i == 100);
  
  var counter = 0;
  
  for (i = 0;i < 200;i++) {
    if (i % 2 == 0) continue;
    counter++;
    }
  TEST("exits 2",counter == 100);
  
  counter = 0;
  outer:
  for (i = 0;i < 20;i++) {
    for (var j = 0;j < 20;j++) {
      if (j == i) continue outer;
      counter++;
      }
    }
  TEST("exits 3",counter == 190);
  counter;
  
  var flag = 0;
  
  non_local_exit: {
    var i = 0;
    i++;
    flag = 2;
    break non_local_exit;
    flag = 1;
    }
  TEST("exits 4",flag == 2);
  
  i = 0;
  counter = 0;
  loop: while (i < 10) {
    another_loop: while (i < 20) {
      break loop;
      counter++;
      }
    counter++;
    }
  TEST("exits 5",counter == 0);
  }

// test switch statement ------------------------------------------------------
{ var count1 = 0,count2 = 0,count3 = 0,defcount = 0,i;

  for (i = 0;i < 10;i++) {
    switch (i) {
      0;
      case 1: count1++;
      case 2: count2++;
      case 3: count3++; break;
      default: defcount++;
      }
    }
  TEST("switch",count1 == 1 && count2 == 2 && count3 == 3 && defcount == 7);
  }

// test arrays ----------------------------------------------------------------
{ function faculty(n) {
    var counter,result = 1;
    for (counter = 1;counter <= n ;counter++)
      result *= counter;
    return result;
    }
  
  var a = new Array(10);
  a[5] = 4;
  TEST("arrays 1",a[5] == 4);
  
  var i;
  a = new Array(1,1,2,6,24,120,720,5040,40320,362880,3628800);
  for (i = 0;i <= 10;i++)
    TEST("arrays "+(2+i),a[i] == faculty(i));
  
  TEST("arrays 13",a.length == 11);
  a.reverse();
  TEST("arrays 14",a[0] == 3628800);
  a.reverse();
  for (i = 0;i <= 10;i++)
    TEST("arrays "+(2+i),a[i] == faculty(i));
  TEST("arrays 15",a.pop() == 3628800);
  TEST("arrays 16",a.length == 10);
  a.push(15);
  TEST("arrays 17",a[10] == 15);
  
  for (i = 11;i <= 2000;i++)
    TEST("arrays 18",a[i] == null);
  }

// test library ---------------------------------------------------------------
{ var u = 20;
  TEST("lib 1",eval("4+3+2+1;") == 10);
  TEST("lib 2",parseInt("0xaffe") == 0xAFFE);
  TEST("lib 3",parseFloat("3.14") == 3.14);
  TEST("lib 10",0 <= Math.random() && Math.random() <= 1);
  TEST("lib 11",Math.abs(Math.sin(Math.PI)) < 0.0001);
  
  var usin = Math.sin;
  TEST("lib 12",Math.abs(usin(Math.PI)) < 0.0001);
  }

// test classes ---------------------------------------------------------------
{ 
  class flupp {
    static const gravity = 9.81;
    static var u = new Array();
    var v = new Array();
    
    constructor function flupp(x) {
      v.push(x);
      }
    static function getGravity() {
      return gravity;
      }
    }
  class gummiflupp extends flupp {
    var elasticity;
    
    constructor function gummiflupp(_elasticity) {
      elasticity = _elasticity;
      super(17);
      }
    function f(x) {
      return elasticity*Math.cos(x)*getGravity();
      }
    }
  
  TEST("class 1",gummiflupp.gravity == gummiflupp.getGravity());
  
  var f = new gummiflupp(7);
  TEST("class 2",f.f(0) > 7*9.8);
  TEST("class 3",f.v[0] == 17);

  var u = 3;
  class scope_test {
    var u = 4;
    function test() {
      u;
      }
    };
  var v = new scope_test();
  TEST("class 4",v.test() == 4);
  }

// output main result ---------------------------------------------------------
if (failed_tests == "") {
  "OK: " + tests.toString() + " tests completed";
  }
else {
  "failed: " + failed_tests;
  }
