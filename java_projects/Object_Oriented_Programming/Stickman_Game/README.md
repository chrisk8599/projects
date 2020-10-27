### Coding Style
<a href="https://oracle.com/technetwork/java/codeconventions-150003.pdf">Oracle</a>

### Location of the Configuration file
src/main/resources/level_1.json , src/main/resources/TEST_1.json, src/main/resources/TEST_2.json

### Description of the Configuration file
Each config file has the hero as its own JSONObject.
The immovable, movable and enemy entities are all stored in
three separate JSON arrays. Each entity that belongs to an
array requires attributes specific to that array. This facilitates
the creation process and allows you to add a new entity anywhere in
its corresponding JSON array. Additionally, there is a set time limit for each config file, corresponding
to the time limit of the specific level. Each config file will have the name
of the next config file (next level) within it. If the config file has an empty string
as the name of the next level. This indicates that this config file is the last level.



### Description of Keyboard input
The movement of the character can be done through the arrow keys.
You can only save your progress once by pressing 's'. You can reload
this saved progress any number of times by pressing 'q'.

## Acknowledgements
<a href="https://opengameart.org/content/top-down-2d-metal-box">Block png</a><br>
