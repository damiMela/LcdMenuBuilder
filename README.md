# LcdMenuBuilder

1. [ Usage. ](#usage)
   - [ Library Setup. ](#setup)
   - [Building a menu. ](#build_menu)
   - [Navigation](#navigation)
2. [Custom Menu Items](#custom_items)

<a name="usage"></a>

## Usage

<a name="setup"></a>

### Library setup

This library uses a callback to print each line of the menu. it must be set with the static method
`MenuSystem::SetPrintCallback(my_print_callback)`.

An example of that callback could be the following:

```c++
void print(uint8_t line, std::string text)
{
	static std::array<std::string, 4> display;
	display[line] = text;
	std::cout << "\033[2J"; // ANSI escape code to clear screen
	std::cout << "\033[H";	// Move cursor to home position
	for (const auto &s : display)
		std::cout << s << std::endl;
}
```

---

<a name="build_menu"></a>

### Building a menu

This library counts with the following rady-made interfaces for the menus:

- **SubMenu**: is a navigable interface the list other menuItems and lets you enter those subItems
- **CheckBoxList**: displays multiple options that can be set to true or false.
- **RadioList**: displays multiple options but lets you select one of those.
- **TextInput**: lets you enter a text.

Besides the "SubMenu" item, each of the above mentioned widgets lets you specify a reference variable to store the value or a handling method that is called when "enter" key is called.

To create a menu a MenuSystem object should be created and then started.

```c++
std::vector<std::string> options = {"option 1", "option 2", "option 3"};

std::vector<std::shared_ptr<MenuItem>> subMenu{
    std::make_shared<TextInputItem>("Text input (handler)", testTextHandler),
    std::make_shared<TextInputItem>("Text input (shared)", buffer)
};

MenuSystem m({
    std::make_shared<SubMenu>("Sub Menu", subMenu),
    std::make_shared<CheckBoxList>("check box", checkListReuslt, options)
});

m.start()

```

---

<a name="navigation"></a>

### Navigation

User input is provided by the implementation. It should call the following methods accordignly

- `void Input(MenuNav::MenuNavInput_e input)`
- `void Input(char input)`

the available navegation interactions are

```c++
	typedef enum{
		ARROW_UP,
		ARROW_DOWN,
		ARROW_LEFT,
		ARROW_RIGHT,
		ENTER_KEY,
		CANCEL_KEY,
		BACKSPACE_KEY
	}MenuNavInput_e;
```

<a name="custom_items"></a>

## Custom Menu Items

For making custom Menu items a class that derives from MenuItem should be created. Every element that derives from MenuItem can be used in SubMenus or as a Main Menu item

```c++
class CheckBoxList : public MenuItem{
public:
	CheckBoxList(const std::string title) : MenuItem(title){}
	virtual ~CheckBoxList();

	void Render() override {
        for(int i = 0; i < MenuConfig::heigth; i++){
            if(i == 0)
                MenuConfig::print(i, std::to_string(currSelection));
            else
                 MenuConfig::print(i, "");
        };

    void Input(MenuNav::MenuNavInput_e input) override {
        if(input == MenuNav::ARROW_UP)
            currSelection++;
        else
            currSelection--;
    };

    void Input(char input) override{};

private:
	uint8_t currSelection = 0;
};
```

## TODO:

- auto rolling text
- Add InlineRender for subMenu rendering
- add numericUpDown
- add horizontal selection
- add method/ctor parameter to pass "not allowed chars" list in TextInput
- limit text width
