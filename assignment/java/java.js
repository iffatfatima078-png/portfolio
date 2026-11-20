// let a=6;
// let b=7;
// console.log(a==b)
// console.log(a===b)
// console.log(a!=b)
// console.log(a!==b)
// let hobby = "dancing";
// if(hobby == "coding"){
//  console.log("** I love coding too! **");
// } else {
//  console.log("** Can you teach me that? **")
// }
let myvariable=false;
if(myvariable){
    console.log("this is true ")
}
if(!myvariable){
    console.log("this is invalid")
}
else{
    console.log("this is not true")
}
// 1. Ask the user's age
let ageInput = prompt("Please enter your age:");

// 2. Convert the response to a number
let age = Number(ageInput);

// 3. Declare a message variable
let message = "";

// 4–6. Use if / else if / else logic
if (age >= 21) {
  message = "You may enter the venue and are allowed to purchase alcohol.";
} else if (age >= 19) {
  message = "You may enter the venue, but you are not allowed to purchase alcohol.";
} else {
  message = "Entry denied. You are not old enough to enter the venue.";
}

// 7. Output the message to the console
console.log(message);
console.log(typeof age)

