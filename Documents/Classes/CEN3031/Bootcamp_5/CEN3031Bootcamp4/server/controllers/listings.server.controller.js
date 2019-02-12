
/* Dependencies */
var mongoose = require('mongoose'), 
    Listing = require('../models/listings.server.model.js');

/*
  In this file, you should use Mongoose queries in order to retrieve/add/remove/update listings.
  On an error you should send a 404 status code, as well as the error message. 
  On success (aka no error), you should send the listing(s) as JSON in the response.

  HINT: if you are struggling with implementing these functions, refer back to this tutorial 
  from assignment 3 https://scotch.io/tutorials/using-mongoosejs-in-node-js-and-mongodb-applications
 */

/* Create a listing */
exports.create = function(req, res) {

  /* Instantiate a Listing */
  var listing = new Listing(req.body);


  /* Then save the listing */
  listing.save(function(err) {  
    if(err) {
      console.log(err);
      res.status(400).send(err);
    } else {
      res.json(listing);  
    }
  });
};

/* Show the current listing */
exports.read = function(req, res) {
  /* send back the listing as json from the request */
  res.json(req.listing);
};

/* Update a listing */
exports.update = function(req, res) {
  var listing=req.listing;
  listing.code=req.body.code;
  listing.name=req.body.name;
  listing.address=req.body.address;
  listing.coordinates={ latitude: req.body.latitude, longitude: req.body.longitude}

  listing.save(function(err){

    if (err){
      res.status(400).send(err); // throws error 404 page
      console.log("error saving", err)} // post error to console
    else{res.json(listing)  // saves listing
    console.log("Saved") // console log of saved to confirm
    }
  })
  /* Replace the article's properties with the new properties found in req.body */
  /* Save the article */
};

/* Delete a listing */
exports.delete = function(req, res) {
  var listing = req.listing;
  listing.remove(function(err){
    if (err){res.status(400).send(err); // throws error 404 page
      console.log("error removing", err); // post error to console
    return;
  }
    else{res.end() // remove item
    console.log("Removed") // console log of remove to confirm
    }
  })
  /* Remove the article */
};

/* Retreive all the directory listings, sorted alphabetically by listing code */
exports.list = function(req, res) {
  mongoose.model('Listing', Listing.listingSchema).find({}, function(err, listings){
    if (err){res.status(400).send(err); // throws error 404 page
      console.log("Error Retrieving", err); // post error to console
  return;
}
  else{
    res.json(listings); // retrieves listings
    console.log("Retrieved") // console log of retrieval to confirm
  }
  })
  /* Your code here */
};

/* 
  Middleware: find a listing by its ID, then pass it to the next request handler. 

  Find the listing using a mongoose query, 
        bind it to the request object as the property 'listing', 
        then finally call next
 */
exports.listingByID = function(req, res, next, id) {
  Listing.findById(id).exec(function(err, listing) {
    if(err) {
      res.status(400).send(err);
    } else {
      req.listing = listing;
      next();
    }
  });
};