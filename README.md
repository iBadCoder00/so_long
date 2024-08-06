# SO LONG - A game made in C 💀

<h3>Subject summary</h3>
<p>Create a simple game where the player can move the character around, within a certain bondary. This game also includes collectible items that the player must collect to win the game.
The bonus part includes animations, and enemies that can kill the character by touching it. For detailed information about the project refer to "subject.pdf".</p>

<h3>Key project takeaways</h3>

- Learn about tiles and sprites.  
- Set game rules and events so as to create a more enjoyable gaming experience.  
- Working with graphic libraries.  
- System events and hooks. Manage system events with custom functionality.  
- Learn about the game loop and the rendering of the game elements.  
- Memory management.
- Learn the basics of 2D animation and frame rates. **(BONUS)**
- Game physics, hitboxes and collision detection algorithms (AABB, SAT...). **(BONUS)**

### Side notes
Despite the project being quite lengthy compared to others, it was rather a pleasant coding experience. The most complex part about this project was creating a basic physics model that allows the character to jump and collide with the elements around it, I wanted to do some realistic force-based physics but ended up using a only-velocity physics model, no mass, with fixed starting velocities and gravity, mostly because I felt that the former was beyond the scope of the project (and it was quite a pain lol). The hitbox also is not 100% precise, it triggers the events a little bit before real collision but it's neglible.  

The linux mlx has a buggy feature where the transparency of the .xpm isn't handled properly so it shows a black pixel instead of a transparent one, I believe this has been fixed but I couldn't find the fix anywhere, that's why I've changed the color value of the pixels to make the black background around the sprites and textures 'disappear'. In a non-buggy version of the mlx the color value of the background pixels should be changed to "None" again in every .xpm file.
### Final grade
125/125
