function hello()
{
var name = prompt("Enter your name :");
document.getElementById("art").innerHTML =" hello , " + name ;
}
function mario()
{
    var  h = 0;
    var mario = "";
    document.getElementById("art").innerHTML = "";
    do
    {
        h = eval(prompt("Enter number bettween 1 and 8 : "));
    }
    while (h > 8 || h < 1);

    for (var ih = 1; ih <= h; ih++)
    {
        for (var shl = 0; shl < ih; shl++)
        {
            mario +="#";
        }

        mario +=" ";

        for (var shr = 0; shr < ih; shr++)
        {
            mario += "#";
        }
        mario += "<br/>";
    }
    document.getElementById("art").innerHTML = mario;
}
function isStringNumeric(str) {
    return /^\d+$/.test(str);
  }

function credit()
{
    document.getElementById("art").innerHTML = ""
   var long_number;
    do{
     long_number = prompt("Enter your number :")
    }while(isStringNumeric(long_number) == false)


    var long = parseInt(long_number)
    var list_1 = 0;
    var list_2 = 0;
    var mod_1;
    var mod_2;
    var d1;
    var d2;
    while (long > 0){
        mod_1 = long % 10
        long = parseInt(long / 10)
        list_1 += mod_1
    
        mod_2 = long % 10
        long = parseInt(long / 10)
        mod_2 = mod_2 * 2
    
        if (mod_2 >= 10){
            d1 = mod_2 % 10
            d2 = parseInt(mod_2 / 10)
            list_2 += d1 + d2
        }
        else{
            list_2 += mod_2
        }
    }
    f_two = parseInt(long_number.slice(0,3))
    count = long_number.length
    
    if ((list_1 + list_2) % 10 == 0){
        if ((f_two == 34 || f_two == 37 ) && count == 15){
            document.getElementById("art").innerHTML = "AMEX"
        }
        else if( (f_two == 51 || f_two == 56) && count == 16){
            document.getElementById("art").innerHTML = "MASTERCARD"
        }
        else if (parseInt(long_number.slice(0,1)) == 4 && (count == 16 || count == 13)){
            document.getElementById("art").innerHTML = "VISA"
        }
        else {
            document.getElementById("art").innerHTML = "INVALID"
        }
    }
        else{
            document.getElementById("art").innerHTML = "INVALID"
        }
    }







function read()
{
document.getElementById("art").innerHTML = "";

var h2 = document.createElement("h2");
h2.innerHTML = "Text : "
document.getElementById("art").appendChild(h2);
h2.id="inside_art"


var newele = document.createElement('textarea');
document.getElementById('art').appendChild(newele);
newele.id = 'injs';
newele.cols = 50;

var b = document.createElement("br");
document.getElementById('art').appendChild(b);

var newbu =document.createElement('button');
newbu.innerHTML = "grade";
document.getElementById('art').appendChild(newbu);
newbu.id = "butjs";
newbu.onclick = readability;
}

function readability(){

    var spa = document.createElement("span")
    document.getElementById("butjs").style.margin = "30px 0 30px 0";
    var br = document.createElement("br")
   document.getElementById("art").appendChild(br)
    document.getElementById("art").appendChild(spa)
    spa.innerHTML = ""
     var letter = 0;
     var word = 1;
     var sen = 0;
    var text = document.getElementById("injs").value
    
    for(var i = 0; i < text.length;i++ ){
       if((text[i] >= "A" && text[i] <= "Z") || (text[i] >= "a" && text[i] <= "z")){
         letter++;
        }
        if(text[i] == " "){
         word++;
        }
        if(text[i] == "?" || text[i] == "!" || text[i] == "."){
         sen++;
        }
     }
     var L = 100 * (letter / word);
     var S = 100 * (sen / word);
     //Final calculation
     var index = Math.round(0.0588 * L - 0.296 * S - 15.8);
    

    
     if (index >= 16)
     {
         spa.innerHTML="Grade 16"
     }
     //If the index number is less than 1
     else if (index < 1)
     {
         spa.innerHTML="Before Grade 1";
     }
     //the original value
     else
     {
         spa.innerHTML = "Grade " + index;
     }

 }