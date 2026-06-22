require("dotenv").config();
const app = require("./src/app");
const connectToDB = require("./src/config/db");

connectToDB()

app.listen(3000, () => {
  console.log("app listening at 3000")
  console.log("Swagger docs available at http://localhost:3000/api-docs")
})