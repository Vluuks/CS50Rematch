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
            moves_start = False

            # this is a very terrible implementation of parsing the file
            for line in f:

                # check if regular info or movement options
                # if it's an enter, make object and clean data
                if line == "\n":
                    rooms.append(Room(line_content[0], line_content[1], line_content[2], options))
                    line_content = []
                    options = []
                    moves_start = False
                # if it's info about the room
                elif line != "-----\n" and not moves_start:
                    line_content.append(line)
                # if it's moves info
                elif line != "-----\n" and moves_start:
                    options.append(line.strip().split())
                # if it's the ----- line indicating the moves are about to follow
                else:
                    moves_start = True

        f.close()
        return rooms

    def load_items(self, file_name):

        with open(file_name, "r") as f:

            # iterate over lines
            for line in f:


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

        # go over items in that room and print them
        for item in a_room.items:
            print(f"{item.name} {item.description}\n")

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

    def play(self):
        """
        Play an Adventure game
        """
        print(f"Welcome, to the Adventure games.\n"
            "May the randomly generated numbers be ever in your favour.\n")

        self.current_room = self.rooms[0]

        # prompt until done
        while not self.won():

            # prompt for input
            self.move_print(self.current_room)
            command = input("> ")

            # check if in valid moves
            moves = set(["EAST", "WEST", "SOUTH", "IN", "OUT", "DOWN", "UP", "LOOK", HELP", "QUIT"])
            if command in moves:

                # quits the game
                if command == "QUIT":
                    print("Thanks for playing!")
                    quit()

                # generates help command info
                elif command == "HELP":
                    self.help_print()

                elif command == "LOOK":
                    self.look_print()

                # it's a movement command
                else:

                    # check with current location's options
                    for option in self.current_room.options:

                        # if the option is present for that room as  well
                        if command == option[0]:
                            print("\nMoving...")
                            print(option[1])

                            # change rooms
                            self.current_room = self.rooms[int(option[1]) - 1]

            # command is not in the defined set
            else:
                print("\n⚠️ Invalid command!\n")


if __name__ == "__main__":
    adventure = Adventure("Tiny")
