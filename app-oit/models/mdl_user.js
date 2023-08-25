const mongoose = require('mongoose');

const Schema = mongoose.Schema;
const model = mongoose.model;

const LoginSchema = new Schema({
    sCorreo: { type: String, required: true },
    sPass: { type: String, required: true },
  },
  {
    collection: 'Login'
  });

const Login = model('Login', LoginSchema);

module.exports = Login;