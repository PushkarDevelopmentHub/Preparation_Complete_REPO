require("dotenv").config()
const mongoose = require("mongoose");

async function connectToDB() { 
  await mongoose.connect(process.env.MONGO_URL).then(()=>{
   console.log("server Connected")
  }).catch(error => {
    console.log("error", error)
    process.exit(1)
  })
}

module.exports = connectToDB;