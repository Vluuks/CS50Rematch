from room import Room
from item import Item
from inventory import Inventory

class Adventure():
    """
    This is your Adventure game class. It should contains
    necessary attributes and methods to setup and play
    Crowther's text based RPG Adventure.
    """
    def __init__(self, game):
        """
        Create rooms and items for the appropriate 'game' version.
        """
        self.rooms = self.load_rooms(f"data/{game}Rooms.txt")
        self.load_items(f"data/{game}Items.txt")
        self.inventory = Inventory()
        self.current_room = None
        self.play()


    def load_rooms(self, file_name):
        """
        Load rooms from filename.
        Returns a collection of Room objects.
        """
        with open(file_name, "r") as f:

            rooms = []
            line_content = []
            options = []
            options_set = []
            options_dict = {}

            moves_start = False

            # this is a very terrible implementation of parsing the file
            for line in f:

                # check if regular info or movement options
                # if it's an enter, make object and clean data
                if line == "\n":
                    rooms.append(Room(line_content[0], line_content[1], line_content[2], options, options_dict, options_set))
                    line_content = []
                    options = []
                    options_dict = {}
                    moves_start = False
                # if it's info about the room
                elif line != "-----\n" and not moves_start:
                    line_content.append(line)
                # if it's moves info
                elif line != "-----\n" and moves_start:

                    # split into command name and rest
                    command_name = (line.strip().split())[0]
                    options_set.append(command_name)

                    # the rest is either just a number or number/requireditem
                    rest = (line.strip().split())[1]

                    # add to the dictionary under that name
                    if command_name in options_dict:
                        options_dict[command_name].append(rest)
                    else:
                        options_dict[command_name] = []
                        options_dict[command_name].append(rest)

                    options.append(line.strip().split())
                # if it's the ----- line indicating the moves are about to follow
                else:
                    moves_start = True

        for room in rooms:
            print(room.name)
            for key in room.options_dict:
                print(key, room.options_dict[key])

        f.close()
        return rooms


    def load_items(self, file_name):
        """
        Loads items and puts them in the right rooms
        """
        with open(file_name, "r") as f:

            # again a rather ineffient way :D
            contents = []
            items = []

            # iterate over lines
            for line in f:

                # append to contents or add to room
                if line == "\n":
                    items.append(Item(contents[0], contents[1], contents[2]))
                    contents = []
                else:
                    contents.append(line)

        # now add them to the right rooms
        for item in items:
            room_index = int(item.room_id) - 1
            self.rooms[room_index].items.append(item)

        f.close()


    def won(self):
        """
        Check if the game is won.
        Returns a boolean.
        """
        # TODO: Define the win condition for Adventure.
        return False


    def move(self, direction):
        """
        Moves to a different room in the specified direction.
        """
        # check with options in room
        for option in self.current_room.options:

            # if the option is present for that room as  well
            if command == option[0]:
                print("\nMoving...")
                print(option[1])
                self.current_room = self.rooms[int(option[1]) - 1]
                return self.current_room
        pass

    def help_print(self):
        """
        Prints help message.
        """

        print("""  You can move by typing directions such as NORTH/SOUTH/EAST/WEST/IN/OUT
        QUIT quits the game.
        HELP prints instructions for the game.
        INVENTORY lists the item in your inventory.
        LOOK lists the complete description of the room and its contents.
        TAKE <item> take item from the room.
        DROP <item> drop item from your inventory.""")


    def look_print(self, a_room):
        """
        Print stuff that can be found in the room
        """

        # check if there is anything
        if len(a_room.items) > 0:

            # go over items in that room and print them
            for item in a_room.items:
                print("\n")
                print(item)

        else:
            print("\nNothing to be seen here...")


    def move_print(self, a_room):
        """
        Print stuff for every move.
        """

        # flavor
        print("------------------")
        print(a_room.name)
        print(a_room.description)
        print("Where do you want to go?")

        # list options
        for i, option in enumerate(a_room.options):
            print(f"{i + 1}. {option[0]}")


    def player_move(self, option):
        """
        Moves the player in the given direction.
        """

        print("\nMoving...")

        # change rooms
        self.current_room = self.rooms[int(option[1]) - 1]

        # print new info
        self.move_print(self.current_room)


    def player_take(self, item_name):
        """
        Attempts to take an item from the room.
        """

        # check in which room we are and if this room has this item
        for item in self.current_room.items:

            # if the name matches an item in the room
            if item.name.strip() == item_name.strip():

                # add to our inventory
                self.inventory.add(item)

                # remove it from the room
                self.current_room.items.remove(item)

                print(f"\n{item.name.strip()} taken")
                return

        print("\nNo such item exists!")


    def player_drop(self, item_name):
        """
        Attempts to drop an item from inventory.
        """
        # check items in teh inventory
        for item in self.inventory.items:

            # if the name matches an item in the inventory
            if item.name.strip() == item_name.strip():

                # add to the room
                self.current_room.items.append(item)

                # remove it from the inventory
                self.inventory.remove(item)

                print(f"\n{item.name.strip()} dropped")
                return

        print("\nYou do not have this item on you!")


    def play(self):
        """
        Play an Adventure game
        """
        print(f"Welcome, to the Adventure games.\n"
            "May the randomly generated numbers be ever in your favour.\n")

        # starting info
        self.current_room = self.rooms[0]
        self.move_print(self.current_room)

        # prompt until done
        while not self.won():

            # prompt for input
            command = input("> ")

            # check if in valid moves
            moves = set(["EAST", "WEST", "SOUTH", "IN", "OUT", "DOWN", "UP", "NORTH"])
            other = set(["LOOK", "HELP", "QUIT"])
            inv = set(["TAKE", "DROP"])

            # if it's some kind of command
            if command in other:

                # quits the game
                if command == "QUIT":
                    print("\nThanks for playing!")
                    quit()

                # generates help command info
                elif command == "HELP":
                    self.help_print()

                elif command == "LOOK":
                    self.look_print(self.current_room)

                else:
                    print("\nUnkown command.")

            # it's a movement command
            elif command in moves:

                    # check with current location's options
                    for option in self.current_room.options:

                        # if the option is present for that room as  well
                        if command == option[0]:
                            self.player_move(option)

            # it's an inventory related command
            elif (command.split())[0] in inv:

                # try to take the item
                if (command.split())[0] == "TAKE":
                    self.player_take((command.split())[1])

                # try to drop the item
                elif (command.split())[0] == "DROP":
                    self.player_drop((command.split())[1])

            # command is not in the defined set
            else:
                print("\n⚠️ Invalid command!\n")


if __name__ == "__main__":
    adventure = Adventure("Small")
