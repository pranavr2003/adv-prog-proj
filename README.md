# Advanced Programming Project
## A C++ port of a subset of Python's Sierra library

This is a C++ port of Python' Sierra library, the source code for which can be found [here](https://github.com/BrainStormYourWayIn/sierra).

The functions have been named the same as in the original library. 

-------------------------------------------------------------------------------------------------------------

### To run:

```bash
cd sierra_port/
g++ main.cpp table.cpp custom_tags.cpp bullets_and_lists.cpp -o main && ./main
```

An `index.html` and `style.css` file will be created upon compilation. They are the output files generated. 

-------------------------------------------------------------------------------------------------------------

### Functions and behavior

We've had to make adjustments and do away with certain features like context-managers and decorators, a native HTML parsing library, pandas etc. which were originally used, in order to make them usable in C++. Here's a few cases where the behaviour has been modified:

- The context-manager behavior has been replicated with constructors and destructors.
- In the absence of `bs4`, a native HTML parser has been written from scratch, albeit with lesser efficiency than the original one which called the `.prettify()` from BeautifulSoup.
- The specific functionalities of `pandas` that were originally used have been written in C++, which involves extracting the rows and columns from a CSV.

-------------------------------------------------------------------------------------------------------------

An example demonstrating the available functions have been included in the `main()` functions of `main.cpp`:

```c++
title("My Webpage", "favicon.ico");
    addFont("https://fonts.googleapis.com/css2?family=Roboto:wght@300&display=swap");
    head("Welcome to My Webpage", "h1", { {"color", "blue"}, {"text-align", "center"} });

    Image img("example.jpg", { {"alt", "Example Image"}, {"width", "300px"} });
    img.show();
    img.css({ {"border-radius", "10px"}, {"box-shadow", "2px 2px 10px gray"} });
    
    Table table;
    table.get_table("test.csv", {{"class", "data"}});
    table.css({{"border-collapse", "collapse"}, {"width", "50%"}, {"border", "1px solid black"}});

    Tag div("div", { {"class", "container"}, {"id", "main"} });
    Tag p("p", {}, "Hello, World!");
    CmTag section("section", { {"class", "wrapper"}, {"style", "color: white; background-color: purple"} });
    section.enter();
    div.render();
    p.render();
    section.exit();

    try {
        Bullets b(true, {"Item 1", "Item 2", "Item 3"}, {{"class", "bullet-list"}, {"id", "my-list"}});
        b.enter();
        b.exit();
    } catch (const exception& e) {
        cerr << "Exception: " << e.what() << endl;
    }

    autoPrettify();
    return 0;
```
