Challenge 1 - ASCII Boat

![image (2)](https://github.com/user-attachments/assets/485651bd-c324-4735-accb-52e63aa5573e)

Challenge 1 was very simple. By honing in my artistic skills, I was able to draw out a boat using ascii art.

 

----------------------------------------------------------------------------------------------------------------------------------------

 

Challenge 2 - Inputting Player Details

![ArchOBSgif](https://github.com/user-attachments/assets/4136188c-d71c-447b-8242-9005ac17ca13)

This took me 2 attempts as the first time I did it, I realised that my code was terrible. This made me want to rewrite it to be a little more readable.

Even though I rewrote it, this still took less time that drawing out the boat using just text.

 

----------------------------------------------------------------------------------------------------------------------------------------

 

Challenge 3 - Calculator

![Math](https://github.com/user-attachments/assets/1566a34a-1c26-49c4-99a2-c15dda5e4aa4)

This didn't take too long as I was able to use the premade (fabs, pow, sqrt, floor, ceil, and round) inside of the cmath library.

To prevent somebody writing regular text instead of an integer or a float, you can create a failsafe.

![Idot](https://github.com/user-attachments/assets/03b6500a-31f2-4330-af60-fb96e345c295)


 

----------------------------------------------------------------------------------------------------------------------------------------

 

Challenge 4 - Text Boxes

![image (3)](https://github.com/user-attachments/assets/ab577074-9e50-446a-81c7-89c0c41eacba)

The reason there are 5 different screenshots is because I am showing the different stages of the program. I decided to iterate instead of trying to do it all in one. This one took me the longest because it took me a second to wrap around the instructions.

![image (4)](https://github.com/user-attachments/assets/4a3eff73-d729-4189-a46d-338daa358510)

This shows that when you either leave the string blank or just spaces, it will produce an error using cerr.

 

----------------------------------------------------------------------------------------------------------------------------------------

 

Challenge 5 - Text Casing

Lorem Ipsum

 

----------------------------------------------------------------------------------------------------------------------------------------



Text Based Adventure

For this text based game, I decided that instead of making a regular small game, I would try and make this as big as I possibly could just for the fun of it.

To start off with, I made a "skeleton" of the game where I have multiple functions that I can call from the main game loop in the main function. This means that from here, I can easily add on the the game instead of having to rewrite everything each time.

![image (5)](https://github.com/user-attachments/assets/91b4d953-8f68-4472-93ac-1670d1eb4189)

This is the first example of the game. It starts you off with some text explaining who you are and the player is given a list of commands to play around with.

When the user clicks play, the first thing the program does, is create a random seed for the game as I want this to be random each time you play it. It will have a structure of a sentence and will have different words and locations and objects to randomly select from to keep the game different.

![image (6)](https://github.com/user-attachments/assets/1bca158a-fe43-49aa-8f62-d6f451b21a07)

I am also experimenting with new data types that I have never had the chance to use before. This is a map. As seen in the comment, this allows you to essentially create a pair. It's like looking at a burger on a menu and in smaller text underneath, it says it comes with fries. In that case, the fries are the pair with the burger. It is that added extra on the the previously single variable.

![image (7)](https://github.com/user-attachments/assets/a0de138f-c188-4c7f-b04b-344a27a4d48a)

So far, all of these commands work but are lacking content (as previously mentioned, it is the skeleton of the game right now)

Continuing on, I have now added a failsafe for the user. Because the commands are all displayed as being uppercase but all of the commands require a lowercase input, I made it so that whatever the user inputs, it will take that string and make it all lowercase. This was harder that I initially thought because I wasn't able to use the transform(tolower). I am not sure why but I managed to get a working solution after following this C++ LowerCase page.

![image (8)](https://github.com/user-attachments/assets/621b10f2-871e-4227-ba56-4c6fd4571b0a) ![image (9)](https://github.com/user-attachments/assets/62f610b1-2a87-41f5-b357-df14eaa73712)

This code works because the ASCII character encoding for uppercase letters range from 65-90. By adding 32 to an uppercase character, it moves it into the range of lowercase letters, therefore, it checks if the string has characters between A and Z then for each letter, it adds 32 to it to make it lowercase.

Now I have gotten this to work, I am continuing with different parts of the program. Right now, I would like to get the inventory and shop to actually work. This involves me adding many different functions including the inventory system, use item, money management, etc. This means that it is much easier for me to add items and modify them.

![image (10)](https://github.com/user-attachments/assets/2b6924fb-d0a8-4523-b0af-fcea37da48bb)
This is the current state of the game. I am now able to open the shop and purchase some binoculars or cypher kit. Now you can use the items but right now, they don't effect the game.
