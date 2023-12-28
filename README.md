# branch-predictor
A Branch Prediction Evaluation System that compares the effectiveness of the following branch prediction techniques:
- One Bit Bimodal
- Two Bit Bimodal (Saturating Counters)
- GShare
- Tournament
- Branch Target Buffer (BTB)

Usage: `./predictors <input_file> <output_file>`
Example: `./predictors in.txt out.txt`

Note: The in.txt trace file is fairly random hence BTB fails since there is no pattern it can identify for prediction.
