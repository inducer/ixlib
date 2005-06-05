var b64map = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
var invmap = new Array();

for (var i = 0;i < b64map.length;i++)
  invmap[b64map.charCodeAt(i)] = i;

for (var i = 0;i < 128;i++) {
  if (invmap[i] == null)
    write("INVALID,");
  else
    write(invmap[i],",");
  }
writeLn();