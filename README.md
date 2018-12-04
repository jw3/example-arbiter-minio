example use of arbiter in a pdal filter
===

just hackin around, _arbiter ⇒ minio_

### arbiter

- Amalgamation [1fcc7db0](https://github.com/connormanning/arbiter/tree/1fcc7db0d6967ef68ff3a2517da8f685168f7527)

### Configuration

#### environment
- `ARBITER_CONFIG_FILE` || `ARBITER_CONFIG_PATH`

#### example

object with driver names as keys

```json
{
  "s3": {
    "endpoint": "localhost:9000",
    "access": "defaultkey",
    "secret": "defaultkey"
  }
}
```

### see
- https://github.com/connormanning/arbiter
- https://www.minio.io/
- https://github.com/connormanning/entwine/issues/99
- https://github.com/connormanning/arbiter/issues/21
- https://gist.github.com/connormanning/8a1157306c51f315b6403807f0926541
