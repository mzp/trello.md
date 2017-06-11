var path = require('path');

module.exports = {
  entry: "./lib/js/src/bg/index.js",
  devtool: "inline-source-map",
  output: {
    path: __dirname + "/extension/js",
    filename: "bg.bundle.js"
  }
};
