require 'yaml'

Vagrant.configure("2") do |config|
  config.vm.box = "ubuntu/focal64"
  # config.vm.network "forwarded_port", guest: 7777, host: 7777

  # Provisión de la repo
  config.vm.synced_folder ".", "/home/vagrant/jazz_jackrabbit_2", type: "rsync",
  rsync__exclude: ["build/", "cmake-build-debug/", "clion-build/"]
  # Provisión del archivo de tipografía.
  config.vm.provision "file", source: "./assets/Miscellaneous/Jazz-Jackrabbit-2.ttf", destination: "/home/vagrant/Jazz-Jackrabbit-2.ttf"

  # Instalación de dependencias.
  config.vm.provision "shell", inline: <<-SHELL
    sudo chown -R vagrant:vagrant .
    sudo chmod -R u+w .

    sudo apt-get update
    sudo apt-get install -y build-essential cmake git libyaml-cpp-dev libfmt-dev
    sudo apt-get install -y qtbase5-dev qtdeclarative5-dev qt5-qmake qttools5-dev-tools libqt5widgets5 libqt5core5a 
    sudo apt-get install -y libgtest-dev
    sudo apt-get install -y libjpeg-dev libpng-dev libfreetype-dev libopusfile-dev libflac-dev libxmp-dev libfluidsynth-dev libwavpack-dev cmake libmodplug-dev
    sudo apt-get install -y libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev libsdl2-gfx-dev

    # Remove CMakeCache.txt
    find /home/vagrant/jazz_jackrabbit_2 -name CMakeCache.txt -type f -exec rm {} \;

    # Instalación de tipografía.
    mkdir -p /home/vagrant/.local/share/fonts
    mv /home/vagrant/Jazz-Jackrabbit-2.ttf /home/vagrant/.local/share/fonts/
    fc-cache -fv

    # Verificación de permisos
    if [ -d "/home/vagrant/jazz_jackrabbit_2" ]; then
        sudo chown -R vagrant:vagrant /home/vagrant/jazz_jackrabbit_2
        sudo chmod -R u+w /home/vagrant/jazz_jackrabbit_2
    else
        echo "Project directory /home/vagrant/jazz_jackrabbit_2 does not exist."
        exit 1
    fi

    cd /home/vagrant/jazz_jackrabbit_2

    # Se crea el directorio build si no existe
    sudo mkdir -p build
    sudo chown -R vagrant:vagrant /home/vagrant/jazz_jackrabbit_2/build
    sudo chmod -R 755 /home/vagrant/jazz_jackrabbit_2/build
    cd build

    sudo chown -R vagrant:vagrant .
    sudo chmod -R u+w .

    # Compilación
    cmake ..
    make -j$(nproc)
  SHELL
end