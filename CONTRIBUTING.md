This file describes good practices to follow if you want to contribute to this project.

---

# Commit Message Format

(inspired from git commit message from angular style and git-commit-message-convention repository)

The following format is used for commit messages (items within square brackets are optional):
```
<type>(<scope>): <subject>[ (#task)]

[<body>]
```

The idea here is for commit messages to be "short and effective". This means the developer needs to "nuclearize" their commits as much as possible. If you have several things to say in your commit message, then you should have split that into several commits.

## Types

| Type          | Description |
|:-------------:|-------------|
| `feature`     | for new feature implementing commits |
| `fix`         | for bug fix commits |
| `security`    | for security issue fix commits |
| `performance` | for performance issue fix commits |
| `improvement` | for backwards-compatible enhancement commits |
| `breaking`    | for backwards-incompatible enhancement commits |
| `deprecated`  | for deprecated feature commits |
| `refactor`    | for refactoring commits |
| `merge`       | for merge commits |
| `style`       | for coding style commits |
| `test`        | for testing commits |
| `cleanup`     | for commits which remove unused/deprecated files |
| `doc`, `docs` | for documentation commits |
| `example`     | for example code commits |
| `dependency`  | for dependencies upgrading or downgrading commits |
| `i18n`        | for i18n (internationalization) commits |
| `config`      | for configuration commits |
| `build`       | for packaging or bundling commits |
| `ci`          | for continuous integration commits |
| `release`     | for publishing commits |
| `assets`      | for asset file change commits |
| `update`      | for update commits |
| `revert`      | for history revert commits |
| `wip`         | for work in progress commits |

## Scope
The scope could be anything specifying place or category of the commit change.
For example: 'test', 'core', 'repo', 'network', subfolder name, etc...

## Subject
The subject contains a succinct description of the change(s) made:

* don't capitalize first letter
* no period/dot (.) at the end

To skip the automated CI tests, the HEAD commit message on push must contain `[skip ci]`.

## Revert
If the commit reverts a previous commit, it should begin with **revert:**, 
followed by the header of the reverted commit. In the body it should say: 
`This reverts commit <hash>.`, where `<hash>` is the SHA of the commit being reverted.



## Examples

new feature:
```
feature(python): added 'custom expression' option
```

bug fix:
```
fix(network): corrected memory corrumption while passing network objects

Closes #28
```

improve performance:
```
performance(core): improved thread management

Default OpenMP thread dispatch is now tuned to be compatible with outer threads from R 
```

revert:
```
revert: feature(python): added 'custom expression' option

This reverts commit 667ecc1654a317a13331b17617d973392f415f02.
```

skip ci:
```
doc: fixed minor mispelling [skip ci]

CI build is a waste of time for such a tiny mispelling fix. 
```



---

# Coding style

- TODO: write description of coding style
