# Pattern Recognizer

An Pattern Recognizer that uses a Pediction by Partial Matching (PPM) method to get symbol probabilities.

## Using the project

To build the project, type on terminal:

`$ make`

To generate the PPM model to some file, type:

`$ ./bin/recognizer -gen input_file_name1 input_file_name2 ... input_file_nameN k output_file_name`

where:

- **input_file_name[1..N]** are the names of the N files used to generate a model;
- **k** is the max context size in the model;
- **output_file_name** is the name of the model file to be generated.

To check the best pattern for a file, type:

`$ ./bin/recognizer -get input_file_name model_option1 ... model_optionN`

where:

- **input_file_name** is the name of the file to be tested;
- **model_option[1..N]** represents the N models to be verified for pattern match.
