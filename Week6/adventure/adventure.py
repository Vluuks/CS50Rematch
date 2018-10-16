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

        # define win conditions as winning room being the last
        self.winning_room_id = self.rooms[-1].id
        self.wonb = False


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
                    rooms.append(Room(line_content[0], line_content[1], line_content[2], options, options_dict, set(options_set)))
                    line_content = []
                    options = []
                    options_set = []
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
        Returns a boolean. What a magical function this is.
        """
        return self.wonb


    def move(self, direction):
        """
        Checks a move to see if it has a conditional and
        performs that move if the user has the required item.
        If the user does not have the item or there is no conditional,
        perform the regular move instead.
        """

        # grab options from dictionary for that direction
        connections = self.current_room.options_dict[direction]

        # assume no conditional
        room_index = connections[0]

        # if it has a 2nd it means there is also a conditional
        if len(connections) == 2:

            # assume regular index for now
            room_index = connections[1]

            # obtain required item's name
            room_req_item = connections[0].split("/")[1]

            # if the user has the required item
            if self.inventory.contains(room_req_item):

                print(f"You use {room_req_item}")

                # perform move with conditional
                room_index = connections[0].split("/")[0]
                new_room = self.rooms[int(room_index) - 1]
                return new_room

            else:
                print(f"It seems like you need a {room_req_item} to go here...")

        # if we don't have the item or there is no 2nd element
        # meaning there is no condition, just move to standard
        new_room = self.rooms[int(room_index) - 1]
        return new_room


    def forced_move(self, a_room):
        """
        Performs forced move for the current room.
        """

        # get the room we are forced to go to
        room_index = a_room.options_dict["FORCED"][0]

        # get new room
        if room_index != '0':
            new_room = self.rooms[int(room_index) - 1]
        # we won or are dead
        else:
            if int(a_room.id) == self.winning_room_id: #TODO
                self.won = True
                print("Congratulations, you beat the game!")
                quit()
            else:
                self.dead()

        return new_room


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
        print("--------------------------------")
        print(f"[ {(a_room.name.strip()).upper()} ]")
        print(a_room.description.strip())
        print("--------------------------------")


    def options_print(self, a_room):
        """
        Prints options for that room.
        """
        print("Where do you want to go?")
        for i, option in enumerate(a_room.options_set):
            print(f"{i + 1}. {option}")


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


    def dead(self):
        print("Unfortunately, you are dead.")
        print("\nThanks for playing!")
        quit()


    def play(self):
        """
        Play an Adventure game
        """
        print(f"Welcome, to the Adventure games.\n"
            "May the randomly generated numbers be ever in your favour.\n")

        # starting info
        self.current_room = self.rooms[0]
        self.move_print(self.current_room)
        self.options_print(self.current_room)

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

                    # check with current location's options if possible at all
                    if command in self.current_room.options_set:

                        # if so, use direction to perform movement
                        # this reassigns the current room
                        self.current_room = self.move(command)
                        self.move_print(self.current_room)

                        # if the new room has a forced movement in its options
                        if "FORCED" in self.current_room.options_set:
                            self.current_room = self.forced_move(self.current_room)
                            self.move_print(self.current_room)

                        # list new options
                        self.options_print(self.current_room)

            # it's an inventory related command
            elif (command.split())[0] in inv:

                # try to take the item
                if (command.split())[0] == "TAKE" and len(command.split()) > 1:
                    self.player_take((command.split(' ', 1))[1])

                # try to drop the item
                elif (command.split())[0] == "DROP" and len(command.split()) > 1:
                    self.player_drop((command.split(' ', 1))[1])

                # player likely didn't say what they wanted to pick up
                else:
                    print("To drop something or pick something up, specify the item like TAKE *ITEM*")


            # command is not in the defined set whatsoever
            else:
                print("\n⚠️ Invalid command!\n")


if __name__ == "__main__":
    adventure = Adventure("Small")
    adventure.play()