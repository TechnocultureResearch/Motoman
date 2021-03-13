from prompt_toolkit import PromptSession
from prompt_toolkit.completion import WordCompleter
from prompt_toolkit.styles import Style

moto_completer = WordCompleter([
    'exit', "help", "1Motor", "2Motor", "Forward", "Reverse", "Stop"], ignore_case=True)

style = Style.from_dict({
    'completion-menu.completion': 'bg:#008888 #ffffff',
    'completion-menu.completion.current': 'bg:#00aaaa #000000',
    'scrollbar.background': 'bg:#88aaaa',
    'scrollbar.button': 'bg:#222222',
})

def main():
  session = PromptSession(completer=moto_completer)

  while True:
      try:
          text = session.prompt('> ')
      except KeyboardInterrupt:
          continue
      except EOFError:
          break
      else:
          print('You entered:', text)
  print('GoodBye!')

if __name__ == "__main__":
  import os, sys
  sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), ".")))
  main()
