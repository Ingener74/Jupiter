Сборка под Linux

```
# do not forget about submodule --init

export JAVA_HOME=<jdk-root-path>

./install-dependencies.sh

virtualenv ../venv
. ../venv/bin/activate

pip install -r requirements.txt

./build-all.sh
```
