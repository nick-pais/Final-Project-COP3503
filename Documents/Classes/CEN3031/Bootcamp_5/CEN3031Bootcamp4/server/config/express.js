var path = require('path'),  
    express = require('express'), 
    mongoose = require('mongoose'),
    morgan = require('morgan'),
    bodyParser = require('body-parser'),
    config = require('./config'),
    listingsRouter = require('../routes/listings.server.routes');

module.exports.init = function() {
  //connect to database
  mongoose.connect(config.db.uri);

  //initialize app
  var app = express();

  //enable request logging for development debugging
  app.use(morgan('dev'));

  //body parsing middleware 
  app.use(bodyParser.json());

  
  /**TODO
  Serve static files */
  app.use('/client', express.static(__dirname + '/../../client')) // static client
  app.use('/public', express.static(__dirname + '/../../public')) // static public

  /**TODO 
  Use the listings router for requests to the api */
  app.use('/api/listings', listingsRouter) // uses listing router to send request to api

  /**TODO 
  Go to homepage for all routes not specified */ 
  app.all(function(request,response,next){ // using .all to send all routes not specifed to / or homepage
    return response.redirect('/');
  })
  return app; // given
};  