const path = require('path');

module.exports = {
    entry: './src/index.tsx',
    output: {
        filename: 'game_elements.js',
        path: path.resolve(__dirname, '../../res/menus')
    },
    resolve: {
        extensions: [".ts", ".tsx", ".js", ".jsx"]
    },
    module: {
        rules: [
            { test: /\.tsx?$/, exclude: /node_modules/, loader: "babel-loader!ts-loader" }
        ]
    }
};
