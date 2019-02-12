//This file holds any configuration variables we may need 
//'config.js' is typically ignored by git to protect sensitive information, such as your database's username and password
// Username: admin
// Password: gators123
module.exports = {
  db: {
    uri: 'mongodb://admin:gators123@ds149551.mlab.com:49551/bootcamp4', //place the URI of your mongo database here.
  }, 
  port: 8080
};