
def main():
  # session = PromptSession(completer=moto_completer)

  while True:
      try:
          # text = session.prompt('> ')
      except KeyboardInterrupt:
          continue
      except EOFError:
          break
      else:
          print('You entered:', text)
  print('GoodBye!')

if __name__ == "__main__":
  main()
