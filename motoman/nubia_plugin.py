import argparse
from motoman.nubia_context import NubiaExampleContext
from motoman.nubia_status import NubiaExampleStatusBar
from nubia import PluginInterface, CompletionDataSource
from nubia.internal.blackcmd import CommandBlacklist
from pygments.token import Token

class NubiaExamplePlugin(PluginInterface):
  """
  The PluginInterface class is a way to customize nubia for every customer
  use case. It allowes custom argument validation, control over command
  loading, custom context objects, and much more.
  """

  def create_context(self):
    """
    Must create an object that inherits from `Context` parent class.
    The plugin can return a custom context but it has to inherit from the
    correct parent class.
    """
    return NubiaExampleContext()

  def validate_args(self, args):
    """
    This will be executed when starting nubia, the args passed is a
    dict-like object that contains the argparse result after parsing the
    command line arguments. The plugin can choose to update the context
    with the values, and/or decide to raise `ArgsValidationError` with
    the error message.
    """
    pass

  def get_opts_parser(self, add_help=True):
    """
    Builds the ArgumentParser that will be passed to , use this to
    build your list of arguments that you want for your shell.
    """
    opts_parser = argparse.ArgumentParser(
      description="Nubia Example Utility",
      formatter_class=argparse.ArgumentDefaultsHelpFormatter,
      add_help=add_help,
    )
    opts_parser.add_argument(
      "--config", "-c", default="", type=str, help="Configuration File"
    )
    opts_parser.add_argument(
      "--verbose",
      "-v",
      action="count",
      default=0,
      help="Increase verbosity, can be specified " "multiple times",
    )
    opts_parser.add_argument(
      "--stderr",
      "-s",
      action="store_true",
      help="By default the logging output goes to a "
      "temporary file. This disables this feature "
      "by sending the logging output to stderr",
    )
    return opts_parser

  def get_completion_datasource_for_global_argument(self, argument):
    if argument == "--config":
      return ConfigFileCompletionDataSource()
    return None

  def create_usage_logger(self, context):
    """
    Override this and return you own usage logger.
    Must be a subtype of UsageLoggerInterface.
    """
    return None

  def get_status_bar(self, context):
    """
    This returns the StatusBar object that handles the bottom status bar
    and the right-side per-line status
    """
    return NubiaExampleStatusBar(context)

  def getBlacklistPlugin(self):
    blacklister = CommandBlacklist()
    blacklister.add_blocked_command("be-blocked")
    return blacklister

  def get_prompt_tokens(self, context):
    """
     > Note from superclass: Override this and return your own prompt for interactive mode.
     Expected to return a list of pygments Token tuples.
    """
    tokens = [
      (Token.Username, "Motoman"),
      (Token.Colon, ""),
      (Token.Pound, "> "),
    ]
    return tokens

class ConfigFileCompletionDataSource(CompletionDataSource):
  def get_all(self):
    return ["/tmp/c1", "/tmp/c2"]
