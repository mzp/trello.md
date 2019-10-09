FROM ocaml/opam2:debian-stable

USER root

# Install OCaml toolchain
RUN opam update && \
  opam switch 4.09 && \
  echo "eval `opam config env`" > /etc/profile.d/opam.sh && \
  rm -rf /home/opam/opam-repository

RUN rm -rf /var/lib/apt/lists/* && apt-get update

# Install Nodejs toolchain
RUN (curl -sL https://deb.nodesource.com/setup_10.x | bash -) && \
  apt-get install -y nodejs --no-install-recommends && \
  apt-get clean && \
  rm -rf /var/cache/apt/archives/* /var/lib/apt/lists/*

RUN npm install -g --unsafe-perm bs-platform@5.0.6

RUN curl -sS https://dl.yarnpkg.com/debian/pubkey.gpg | apt-key add - && \
      echo "deb https://dl.yarnpkg.com/debian/ stable main" > /etc/apt/sources.list.d/yarn.list && \
      apt-get update && \
      apt-get install -y yarn --no-install-recommends && \
      apt-get clean && \
      sudo rm -rf /var/cache/apt/archives/* /var/lib/apt/lists/*

WORKDIR /trello.md
