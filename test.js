// const myaddon = require('./build/Debug/myaddon');

var myaddon = require('bindings')('myaddon.node')

const result = myaddon.add(3);
console.log('result of add:', result);

// let cb = function(msg){
//     console.log(msg);
// }

// cb = null;
// myaddon.runCallback(cb);