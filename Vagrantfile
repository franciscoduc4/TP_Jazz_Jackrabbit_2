require 'yaml'

# Se carga la configuración desde el archivo YAML.
# Se necesita que el archivo contenga en la clave 'ssh_key_path' el path hacia las claves SSH y que esté configurada la de GitHub para que pueda descargarse la repo.

config_path = File.join(File.dirname(__FILE__), 'src', 'config', 'common.yaml')
config_settings = YAML.load_file(config_path)

Vagrant.configure("2") do |config|
  config.vm.box = "ubuntu/focal64"
  
  # Se usa la clave ssh para clonar la repo, que se obtiene desde el archivo YAML.
  ssh_key_path = config_settings['ssh_key_path']
  config.vm.provision "file", source: ssh_key_path, destination: "/home/vagrant/.ssh/id_rsa"

  # Provisión del archivo de tipografía.
  config.vm.provision "file", source: "./assets/Miscellaneous/Jazz-Jackrabbit-2.ttf", destination: "/home/vagrant/Jazz-Jackrabbit-2.ttf"

  # Instalación de la tipografía.
  config.vm.provision "shell", inline: <<-SHELL
  # Se crea el directorio de tipografías, si no existe.
  mkdir -p /home/vagrant/.local/share/fonts
  
  # Se mueve la tipografía provista al directorio de tipografías.
  mv /home/vagrant/Jazz-Jackrabbit-2.ttf /home/vagrant/.local/share/fonts/
  
  # Actualización del caché de tipografías.
  fc-cache -fv

  # Instalación de dependencias.
  config.vm.provision "shell", inline: <<-SHELL
    sudo apt-get update
    sudo apt-get install -y build-essential cmake qt5-default libqt5widgets5 \
        libqt5core5a libsdl2-dev libyaml-cpp-dev libfmt-dev git \
        qtbase5-dev qtdeclarative5-dev qt5-qmake qttools5-dev-tools \
        libsdl2-image-dev 

    # Se le dan los permisos correspondientes al archivo de claves SSH.
    chmod 600 /home/vagrant/.ssh/id_rsa
    
    # Se setea la SSH para usar la clave del archivo.
    echo "Host github.com\n\tStrictHostKeyChecking no\n\tIdentityFile /home/vagrant/.ssh/id_rsa\n" >> /home/vagrant/.ssh/config

    ssh-keyscan github.com >> /home/vagrant/.ssh/known_hosts

    # Clonado del repositorio
    git clone git@github.com:franciscoduc4/TP_Jazz_Jackrabbit_2.git /home/vagrant/jazz_jackrabbit_2

    # Build
    cd /home/vagrant/jazz_jackrabbit_2
    mkdir build
    cd build
    cmake ..
    make -j$(nproc)
  SHELL
end