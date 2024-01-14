FROM wokwi/builder-clang-wasm

USER root

RUN apk add gcompat libc6-compat python3 curl docker zsh shadow

# Zsh/Oh My Zsh
RUN apk add zsh-autosuggestions zsh-syntax-highlighting
RUN sh -c "$(wget https://raw.github.com/robbyrussell/oh-my-zsh/master/tools/install.sh -O -)"
RUN echo "source /usr/share/zsh/plugins/zsh-syntax-highlighting/zsh-syntax-highlighting.zsh" >> ~/.zshrc && \
    echo "source /usr/share/zsh/plugins/zsh-autosuggestions/zsh-autosuggestions.zsh" >> ~/.zshrc && \
    sed -i 's/^ZSH_THEME=".\+"$/ZSH_THEME=\"gozilla\"/g' ~/.zshrc

# Act, for running Github Actions locally
RUN curl -s https://raw.githubusercontent.com/nektos/act/master/install.sh | BINDIR=/usr/local/bin ash
