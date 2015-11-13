# encoding: utf8

from NextSummerPython import NextSummer

if __name__ == '__main__':
    ns = NextSummer('Main')

    ns.execPythonScript("""

from NextSummerPython import NextSummer

ns = NextSummer('Inside script')

ns.sayHelloNextSummer()

ns.execPythonScript('''

from NextSummerPython import NextSummer
ns = NextSummer('Inside inside script')

''')

""")
