function func() {
    //print("hello world");
    var result = 0;
     for (var i = 0; i < 1000; i++) {
         for (var j = 0; j < 1000; j++) {
             result += i;
         }
      }
     return result;
}
func();