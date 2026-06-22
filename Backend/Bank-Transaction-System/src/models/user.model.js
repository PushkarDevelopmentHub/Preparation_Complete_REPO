const mongoose = require("mongoose");
const bcrypt = require("bcryptjs")

const userSchema = mongoose.Schema({
  email: {
    type: String,
    required: [true, "Email is Required for Creating a User"],
    trim: true,
    lowercase: true,
    match: [/^\w+([\.-]?\w+)*@\w+([\.-]?\w+)*(\.\w{2,3})+$/, 'Please fill a valid email address'],
    unique: [true, "Email already Exists"]
  },
  name: {
    type: String,
    required: [true, "Name is Required for creating an account"]
  },
  password: {
    type: String,
    required: [true, "Password is Required for creating an account"],
    minlength: [6, "password should contain more than 6 character"],
    select: false
  },
},{
  timestamps: true
})

userSchema.pre("save", async function(name) {
  if(!this.isModified("password")){
    return 
  }

  const hash = await bcrypt.hash(this.password, 10)
  this.password = hash
  return  
})


userSchema.methods.comparePassword = async function(password) {
  console.log(password, this.password)
  return await bcrypt.compare(password, this.password)
}

const userModel = mongoose.model("user", userSchema);

module.exports = userModel