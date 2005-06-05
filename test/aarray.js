// simple example script for the usage of AArray

var a = new AArray();

a[0] = 3;
a[1] = 2;
a["foo"] = "bar";
a[3] = "foobar";


// index mode
writeLn( "index mode\n" );

for( var i = 0; i < a.length; ++i )
  writeLn( "\t",  a.key(i), " => ", a(i)  );


// using a function as index
function foo() {}

a[foo] = "foo function";


// changing the key
a.key( a.length - 1 ) = "was function";


// write it out again:
writeLn();

for( var i = 0; i < a.length; ++i )
  writeLn( "\t",  a.key(i), " => ", a(i)  );


// constructors

var b = new AArray( a ); // creates a new array by copying the elements of a
var c = a;              // the result is the same as the line above


// other implemeted funtions of AArray

a.reverse();
a.clear();   

