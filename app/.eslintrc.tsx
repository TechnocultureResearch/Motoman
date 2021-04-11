// Path: /.eslintrc.js

module.exports = {
  parserOptions: {
    sourceType: 'module'
  },
  // extends: ['airbnb-typescript'],
  rules: {
    'react/jsx-filename-extension': 'off',
    // You can override any rules you want
  },
  settings: {
    'import/resolver': {
      node: {
        extensions: ['.js', '.jsx', '.ts', '.tsx'],
        moduleDirectory: ['node_modules', 'src/'],
      },
    },
  },
};
