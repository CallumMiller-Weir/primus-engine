/*
    Copyright (c) 2023 Callum Miller-Weir

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so.

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.

    @author Callum Miller-Weir
 */

#include <iostream>
#include "package/repository.h"

using namespace primus;

int main(int argc, char** argv)
{
    Repository *repo = Repository::empty("repo/");
    repo->addPackage(Package::fromJSON(
        R"(
            {
                "package-id": "package",
                "happy": false
            }
        )"
    ));

    Repository *child = Repository::empty("repo/child/");
    child->addPackage(Package::fromJSON(
        R"(
            {
                "package-id": "package",
                "happy": true
            }
        )"
    ));

    repo->addRepository(child);

    std::string list = repo->list();
    std::cout << list << std::endl;

    return 0;
}